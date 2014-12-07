/*
    ofxHttpUtils v0.3
    Chris O'Shea, Arturo, Jesus, CJ

    Modified: 16th March 2009
    openFrameworks 0.06

*/

#undef verify 

#include "Poco/Net/SSLManager.h"
#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/Net/ConsoleCertificateHandler.h"
#include "Poco/Net/FilePartSource.h"
#include "Poco/Net/StringPartSource.h"
#include "Poco/Net/KeyConsoleHandler.h"
#include "Poco/Net/HTTPSession.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/StreamCopier.h"
#include "Poco/Path.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"

#include "ofxHttpUtils.h"
#include "ofEvents.h"

using namespace std;
using namespace Poco;
using namespace Poco::Net;

bool ofxHttpUtils::initialized = false;

// ----------------------------------------------------------------------
ofxHttpUtils::ofxHttpUtils(){
    timeoutSeconds = 2;
    verbose = true;
    sendCookies = true;
    //start();

    if(!initialized){
    	SharedPtr<PrivateKeyPassphraseHandler> pConsoleHandler = new KeyConsoleHandler(false);
    	SharedPtr<InvalidCertificateHandler> pInvalidCertHandler = new ConsoleCertificateHandler(true);
    	Context::Ptr pContext = new Context(Context::CLIENT_USE, "", Context::VERIFY_NONE);
    	SSLManager::instance().initializeClient(pConsoleHandler, pInvalidCertHandler, pContext);
    	initialized = true;
    }
}

// ----------------------------------------------------------------------
ofxHttpUtils::~ofxHttpUtils(){
}

// ----------------------------------------------------------------------
ofxHttpResponse ofxHttpUtils::submitForm(ofxHttpForm form){
	return doPostForm(form);
}

// ----------------------------------------------------------------------
void ofxHttpUtils::addForm(ofxHttpForm form){
	lock();
    forms.push(form);
    condition.signal();
    unlock();
}

// ----------------------------------------------------------------------
void ofxHttpUtils::start() {
    startThread(true, false);
}

// ----------------------------------------------------------------------
void ofxHttpUtils::stop() {
    stopThread();
    condition.signal();
}

// ----------------------------------------------------------------------
void ofxHttpUtils::threadedFunction(){
	lock();
    while( isThreadRunning() ){
    	if(forms.size()>0){
			ofxHttpForm form = forms.front();
			ofxHttpResponse response;
	    	unlock();
			if(form.method==OFX_HTTP_POST){
				response = doPostForm(form);
				ofLogVerbose("ofxHttpUtils") << "(thread running) form submitted (post): "  << form.name;
			}else{
				string url = generateUrl(form);
				ofLogVerbose("ofxHttpUtils") << "form submitted (get):" << form.name;
				response = getUrl(url);
			}
    		lock();
			if(response.status!=-1) forms.pop();
    	}
    	if(forms.empty()){
    	    ofLogVerbose("ofxHttpUtils") << "empty, waiting";
    		condition.wait(mutex);
    	}
    }
    unlock();
    ofLogVerbose("ofxHttpUtils") << "thread finished";
}

// ----------------------------------------------------------------------
int ofxHttpUtils::getQueueLength(){
    Poco::ScopedLock<ofMutex> lock(mutex);
    return forms.size();
}

// ----------------------------------------------------------------------
void ofxHttpUtils::clearQueue(){
    Poco::ScopedLock<ofMutex> lock(mutex);
    while(!forms.empty()) forms.pop();
}

// ----------------------------------------------------------------------
string ofxHttpUtils::generateUrl(ofxHttpForm & form) {
    // url to send to
    string url = form.action;

    // do we have any form fields?
    int numfields = form.formIds.size();
    if(numfields > 0){
        url += "?";
        for(int i=0;i<numfields;i++){
            url += form.formIds[i] +"="+ form.formValues[i];
            if(i<numfields-1)
                url += "&";
        }
    }
    return url;
}

ofxHttpResponse ofxHttpUtils::postData(string url, const ofBuffer & data,  string contentType){
	ofxHttpResponse response;
	try{
		URI uri( url.c_str() );
		std::string path(uri.getPathAndQuery());
		if (path.empty()) path = "/";

		//HTTPClientSession session(uri.getHost(), uri.getPort());
		HTTPRequest req(HTTPRequest::HTTP_POST, path, HTTPMessage::HTTP_1_1);
		if(auth.getUsername()!="") auth.authenticate(req);

		if(sendCookies){
			for(unsigned i=0; i<cookies.size(); i++){
				NameValueCollection reqCookies;
				reqCookies.add(cookies[i].getName(),cookies[i].getValue());
				req.setCookies(reqCookies);
			}
		}

		if(contentType!=""){
			req.setContentType(contentType);
		}

		req.setContentLength(data.size());

		HTTPResponse res;
		ofPtr<HTTPSession> session;
		istream * rs;
		if(uri.getScheme()=="https"){
			HTTPSClientSession * httpsSession = new HTTPSClientSession(uri.getHost(), uri.getPort());//,context);
			httpsSession->setTimeout(Poco::Timespan(20,0));
			httpsSession->sendRequest(req) << data;
			rs = &httpsSession->receiveResponse(res);
			session = ofPtr<HTTPSession>(httpsSession);
		}else{
			HTTPClientSession * httpSession = new HTTPClientSession(uri.getHost(), uri.getPort());
			httpSession->setTimeout(Poco::Timespan(20,0));
			httpSession->sendRequest(req) << data;
			rs = &httpSession->receiveResponse(res);
			session = ofPtr<HTTPSession>(httpSession);
		}

		response = ofxHttpResponse(res, *rs, url);

		if(sendCookies){
			cookies.insert(cookies.begin(),response.cookies.begin(),response.cookies.end());
		}

		if(response.status>=300 && response.status<400){
			Poco::URI uri(req.getURI());
			uri.resolve(res.get("Location"));
			response.location = uri.toString();
		}

		ofNotifyEvent(newResponseEvent, response, this);
	}catch (Exception& exc){

    	ofLogError("ofxHttpUtils") << "ofxHttpUtils error postData--";

        //ofNotifyEvent(notifyNewError, "time out", this);

        // for now print error, need to broadcast a response
    	ofLogError("ofxHttpUtils") << exc.displayText();
        response.status = -1;
        response.reasonForStatus = exc.displayText();
    	ofNotifyEvent(newResponseEvent, response, this);

    }
	return response;
}

// ----------------------------------------------------------------------
ofxHttpResponse ofxHttpUtils::doPostForm(ofxHttpForm & form){
	ofxHttpResponse response;
    try{
        URI uri( form.action.c_str() );
        std::string path(uri.getPathAndQuery());
        if (path.empty()) path = "/";

        //HTTPClientSession session(uri.getHost(), uri.getPort());
		HTTPRequest req(HTTPRequest::HTTP_POST, path, HTTPMessage::HTTP_1_1);
		if(auth.getUsername()!="") auth.authenticate(req);

		if(sendCookies){
			for(unsigned i=0; i<cookies.size(); i++){
				NameValueCollection reqCookies;
				reqCookies.add(cookies[i].getName(),cookies[i].getValue());
				req.setCookies(reqCookies);
			}
		}

        HTTPResponse res;
		HTMLForm pocoForm;
		// create the form data to send
	    if(form.formFiles.size()>0)
			pocoForm.setEncoding(HTMLForm::ENCODING_MULTIPART);
		else
			pocoForm.setEncoding(HTMLForm::ENCODING_URL);

		// form values
		for(unsigned i=0; i<form.formIds.size(); i++){
			const std::string name = form.formIds[i].c_str();
			const std::string val = form.formValues[i].c_str();
			pocoForm.set(name, val);
		}

		map<string,string>::iterator it;
		for(it = form.formFiles.begin(); it!=form.formFiles.end(); it++){
			string fileName = it->second.substr(it->second.find_last_of('/')+1);
			ofLogVerbose("ofxHttpUtils") << "adding file: " << fileName << " path: " << it->second;
			pocoForm.addPart(it->first,new FilePartSource(it->second));
		}

        pocoForm.prepareSubmit(req);

        ofPtr<HTTPSession> session;
        istream * rs;
        if(uri.getScheme()=="https"){
        	HTTPSClientSession * httpsSession = new HTTPSClientSession(uri.getHost(), uri.getPort());//,context);
        	httpsSession->setTimeout(Poco::Timespan(20,0));
            pocoForm.write(httpsSession->sendRequest(req));
        	rs = &httpsSession->receiveResponse(res);
        	session = ofPtr<HTTPSession>(httpsSession);
        }else{
        	HTTPClientSession * httpSession = new HTTPClientSession(uri.getHost(), uri.getPort());
        	httpSession->setTimeout(Poco::Timespan(20,0));
            pocoForm.write(httpSession->sendRequest(req));
        	rs = &httpSession->receiveResponse(res);
        	session = ofPtr<HTTPSession>(httpSession);
        }

		response = ofxHttpResponse(res, *rs, form.action);

		if(sendCookies){
			cookies.insert(cookies.begin(),response.cookies.begin(),response.cookies.end());
		}

		if(response.status>=300 && response.status<400){
			Poco::URI uri(req.getURI());
			uri.resolve(res.get("Location"));
			response.location = uri.toString();
		}

    	ofNotifyEvent(newResponseEvent, response, this);


    }catch (Exception& exc){

    	ofLogError("ofxHttpUtils") << "ofxHttpUtils error doPostForm--";

        //ofNotifyEvent(notifyNewError, "time out", this);

        // for now print error, need to broadcast a response
    	ofLogError("ofxHttpUtils") << exc.displayText();
        response.status = -1;
        response.reasonForStatus = exc.displayText();
    	ofNotifyEvent(newResponseEvent, response, this);

    }

    return response;
}

// ----------------------------------------------------------------------
ofxHttpResponse ofxHttpUtils::getUrl(string url){

   ofxHttpResponse response;
   try{
		URI uri(url.c_str());
		std::string path(uri.getPathAndQuery());
		if (path.empty()) path = "/";

		HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);

		if(auth.getUsername()!="") auth.authenticate(req);

        if(sendCookies){
        	for(unsigned i=0; i<cookies.size(); i++){
        		NameValueCollection reqCookies;
        		reqCookies.add(cookies[i].getName(),cookies[i].getValue());
        		req.setCookies(reqCookies);
        	}
        }

		HTTPResponse res;
        ofPtr<HTTPSession> session;
        istream * rs;
        if(uri.getScheme()=="https"){
        	HTTPSClientSession * httpsSession = new HTTPSClientSession(uri.getHost(), uri.getPort());//,context);
        	httpsSession->setTimeout(Poco::Timespan(timeoutSeconds,0));
        	httpsSession->sendRequest(req);
        	rs = &httpsSession->receiveResponse(res);
        	session = ofPtr<HTTPSession>(httpsSession);
        }else{
        	HTTPClientSession * httpSession = new HTTPClientSession(uri.getHost(), uri.getPort());
        	httpSession->setTimeout(Poco::Timespan(timeoutSeconds,0));
        	httpSession->sendRequest(req);
        	rs = &httpSession->receiveResponse(res);
        	session = ofPtr<HTTPSession>(httpSession);
        }

		response=ofxHttpResponse(res, *rs, url);

		if(sendCookies){
			cookies.insert(cookies.begin(),response.cookies.begin(),response.cookies.end());
		}

		if(response.status>=300 && response.status<400){
			Poco::URI uri(req.getURI());
			uri.resolve(res.get("Location"));
			response.location = uri.toString();
		}

		ofNotifyEvent( newResponseEvent, response, this );

		//std::cout << res.getStatus() << " " << res.getReason() << std::endl;
		//StreamCopier::copyStream(rs, std::cout);

	}catch (Exception& exc){
		ofLogError("ofxHttpUtils") << exc.displayText();
        response.status = -1;
        response.reasonForStatus = exc.displayText();
    	ofNotifyEvent(newResponseEvent, response, this);
	}
	return response;

}

// ----------------------------------------------------------------------
void ofxHttpUtils::addUrl(string url){
	ofxHttpForm form;
	form.action=url;
	form.method=OFX_HTTP_GET;
    form.name=form.action;

	addForm(form);
}

// ----------------------------------------------------------------------
void ofxHttpUtils::sendReceivedCookies(){
	sendCookies = true;
}

// ----------------------------------------------------------------------
void ofxHttpUtils::setBasicAuthentication(string user, string password){
	auth.setUsername(user);
	auth.setPassword(password);
}

