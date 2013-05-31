/*
    ofxHttpUtils v0.3
    Chris O'Shea, Arturo, Jesus, CJ

    Modified: 16th March 2009
    openFrameworks 0.06

*/


#include "ofxHttpUtils.h"
#include "ofEvents.h"
#include "Poco/Net/FilePartSource.h"

using namespace std;

// ----------------------------------------------------------------------
ofxHttpUtils::ofxHttpUtils(){
    timeoutSeconds = 2;
    verbose = true;

    //start();
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
    unlock();
}

// ----------------------------------------------------------------------
void ofxHttpUtils::start() {
    	startThread(true, false);
        printf("thread started\n");
}
// ----------------------------------------------------------------------
void ofxHttpUtils::stop() {
    stopThread();

}
// ----------------------------------------------------------------------
void ofxHttpUtils::threadedFunction(){

    // loop through this process whilst thread running
    while( isThreadRunning() == true ){
		lock();
    	if(forms.size()>0){
			ofxHttpForm form = forms.front();
	    	unlock();
			if(form.method==OFX_HTTP_POST){
				doPostForm(form);
				printf("ofxHttpUtils: (thread running) form submitted (post): %s\n", form.name.c_str());
			}else{
				string url = generateUrl(form);
				printf("ofxHttpUtils: (thread running) form submitted (get): %s\n", form.name.c_str());
				getUrl(url);
			}
    		lock();
			forms.pop();
	    	unlock();
    	}else{
    		unlock();
    	}
    	ofSleepMillis(10);
    }

}
// ----------------------------------------------------------------------
int ofxHttpUtils::getQueueLength(){
    // i have taken this out for now
     return 0;
     /*if( lock() ){
         printf("get queue size\n");
        return forms.size();
        unlock();
     }*/
}
// ----------------------------------------------------------------------
void ofxHttpUtils::clearQueue(){
    // i have taken this out for now
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

// ----------------------------------------------------------------------
ofxHttpResponse ofxHttpUtils::doPostForm(ofxHttpForm & form){
	ofxHttpResponse response;
    try{
        URI uri( form.action.c_str() );
        std::string path(uri.getPathAndQuery());
        cout << "ofxHttpUtils::post: "<< uri.getPathAndQuery() << endl;
        if (path.empty()) path = "/";

        HTTPClientSession session(uri.getHost(), uri.getPort());
        HTTPRequest req(HTTPRequest::HTTP_POST, path, HTTPMessage::HTTP_1_1);
        if(auth.getUsername()!="") auth.authenticate(req);

        if(sendCookies){
        	for(unsigned i=0; i<cookies.size(); i++){
        		NameValueCollection reqCookies;
        		reqCookies.add(cookies[i].getName(),cookies[i].getValue());
        		req.setCookies(reqCookies);
        	}
        }

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
        	cout << "adding file: " << fileName << " path: " << it->second << endl;
        	pocoForm.addPart(it->first,new FilePartSource(it->second));
        }

        pocoForm.prepareSubmit(req);

        pocoForm.write(session.sendRequest(req));

        HTTPResponse res;
        istream& rs = session.receiveResponse(res);

		response = ofxHttpResponse(res, rs, path);

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

    	std::cerr << "ofxHttpUtils error--\n";

        //ofNotifyEvent(notifyNewError, "time out", this);

        // for now print error, need to broadcast a response
        std::cerr << exc.displayText() << std::endl;
        response.status = -1;
        response.reasonForStatus = exc.displayText();

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

		HTTPClientSession session(uri.getHost(), uri.getPort());
		HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
		if(auth.getUsername()!="") auth.authenticate(req);
		session.setTimeout(Poco::Timespan(timeoutSeconds,0));
		session.sendRequest(req);
		HTTPResponse res;
		istream& rs = session.receiveResponse(res);

		response=ofxHttpResponse(res, rs, path);

		if(response.status>=300 && response.status<400){
			Poco::URI uri(req.getURI());
			uri.resolve(res.get("Location"));
			response.location = uri.toString();
		}

		ofNotifyEvent( newResponseEvent, response, this );

		//std::cout << res.getStatus() << " " << res.getReason() << std::endl;
		//StreamCopier::copyStream(rs, std::cout);

	}catch (Exception& exc){
		std::cerr << exc.displayText() << "\n";
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

