/*
    ofxHttpUtils v0.3
    Chris O'Shea, Arturo, Jesus, CJ

    Modified: 16th March 2009
    openFrameworks 0.06

*/

#ifndef _OFX_HTTP_UTILS
#define _OFX_HTTP_UTILS

#include "ofMain.h"

#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/HTTPBasicCredentials.h"
#include "Poco/StreamCopier.h"
#include "Poco/Path.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
#include "Poco/Mutex.h"

#include <iostream>
#include <queue>
#include <istream>

using namespace Poco::Net;
using namespace Poco;

class ofxHttpListener;
class ofxHttpEventManager;

#include "ofxHttpTypes.h"

struct ofxHttpResponse{
	ofxHttpResponse(HTTPResponse& pocoResponse, std::istream &bodyStream, string turl, bool binary=false){
		status=pocoResponse.getStatus();
		timestamp=pocoResponse.getDate();
		reasonForStatus=pocoResponse.getReasonForStatus(pocoResponse.getStatus());
		contentType = pocoResponse.getContentType();
		responseBody.set(bodyStream);

        url = turl;
        pocoResponse.getCookies(cookies);
	}

	ofxHttpResponse(){}

	string getURLFilename(){
		return url.substr(url.rfind('/')+1);
	}

	int status; 				// return code for the response ie: 200 = OK
	string reasonForStatus;		// text explaining the status
	ofBuffer responseBody;		// the actual response
	string contentType;			// the mime type of the response
	Poco::Timestamp timestamp;		// time of the response
	string url;
	vector<HTTPCookie> cookies;
	string location;
};

class ofxHttpUtils : public ofThread{

	public:

		ofxHttpUtils();
		~ofxHttpUtils();
		//-------------------------------
		// non blocking functions

		void addForm(ofxHttpForm form);
		void addUrl(string url);

		//-------------------------------
		// blocking functions
		ofxHttpResponse submitForm(ofxHttpForm form);
		ofxHttpResponse getUrl(string url);

        int getQueueLength();
        void clearQueue();

		//-------------------------------
		// threading stuff
		void threadedFunction();

		//------------------------------
		// events
		ofEvent<ofxHttpResponse> newResponseEvent;

        // other stuff-------------------
        void setTimeoutSeconds(int t){
            timeoutSeconds = t;
        }
        void setVerbose(bool v){
            verbose = v;
        }

        void sendReceivedCookies();

        void setBasicAuthentication(string user, string password);


		void start();
        void stop();

    protected:

		bool verbose;
        int timeoutSeconds;
        bool sendCookies;

		//--------------------------------
		// http utils
		string generateUrl(ofxHttpForm & form);
		ofxHttpResponse doPostForm(ofxHttpForm & form);

		std::queue<ofxHttpForm> forms;
		vector<HTTPCookie> cookies;
		HTTPBasicCredentials auth;


};
#endif
