/*
    ofxHttpUtils v0.3
    Chris O'Shea, Arturo, Jesus, CJ

    Modified: 16th March 2009
    openFrameworks 0.06

*/

#ifndef _OFX_HTTP_UTILS
#define _OFX_HTTP_UTILS


#include <iostream>
#include <queue>
#include <istream>

#include "Poco/Mutex.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Condition.h"
#include "Poco/Net/HTTPBasicCredentials.h"

#include "ofThread.h"
#include "ofConstants.h"
#include "ofxHttpTypes.h"
#include "ofEvents.h"


class ofxHttpListener;
class ofxHttpEventManager;

struct ofxHttpResponse{
	ofxHttpResponse(Poco::Net::HTTPResponse& pocoResponse, std::istream &bodyStream, string turl, bool binary=false){
		status=pocoResponse.getStatus();
		try{
			timestamp=pocoResponse.getDate();
		}catch(Poco::Exception & exc){

		}
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
	vector<Poco::Net::HTTPCookie> cookies;
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
		ofxHttpResponse postData(string url, const ofBuffer & data, string contentType="");

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
		vector<Poco::Net::HTTPCookie> cookies;
		Poco::Net::HTTPBasicCredentials auth;
		Poco::Condition condition;

		static bool initialized;

};
#endif
