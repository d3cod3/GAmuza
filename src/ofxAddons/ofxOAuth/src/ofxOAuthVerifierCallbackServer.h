// =============================================================================
//
// Copyright (c) 2010-2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#pragma once


#include <set>
#include "Poco/String.h"
#include "Poco/SharedPtr.h"
#include "Poco/URI.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/NameValueCollection.h"
#include "ofMain.h"
#include "ofxOAuthVerifierCallbackInterface.h"



class ofxOAuthAuthReqHandler: public Poco::Net::HTTPRequestHandler
{
public:
    ofxOAuthAuthReqHandler(ofxOAuthVerifierCallbackInterface* _callback,
                           const std::string& _docRoot):
        callback(_callback),
        docRoot(_docRoot)
    {
    }

    virtual ~ofxOAuthAuthReqHandler()
    {
    }
    
    void handleRequest(Poco::Net::HTTPServerRequest& request,
                       Poco::Net::HTTPServerResponse& response)
    {

        Poco::URI uri(request.getURI());

        response.setChunkedTransferEncoding(true);
        response.setKeepAlive(false);

        ofLogVerbose("ofxOAuthAuthReqHandler::handleRequest") << "request: " << request.getURI();

        // send raw request
        callback->receivedVerifierCallbackRequest(request);
        
        // send the cookies
        Poco::Net::NameValueCollection cookies;

        request.getCookies(cookies);

        if(!cookies.empty())
        {
            callback->receivedVerifierCallbackCookies(cookies);
        }
        else
        {
            ofLogVerbose("ofxOAuthAuthReqHandler::handleRequest") << "Cookies are empty.";
        }

        // send the headers
        if(!request.empty())
        {
            callback->receivedVerifierCallbackHeaders(request);
        }
        else
        {
            ofLogVerbose("ofxOAuthAuthReqHandler::handleRequest") << "Headers are empty.";
        }
        
        Poco::Net::NameValueCollection queryParams;
        parseQuery(uri.getQuery(),queryParams);
        if(!queryParams.empty())
        {
            callback->receivedVerifierCallbackGetParams(queryParams);
        }
        else
        {
            ofLogVerbose("ofxOAuthAuthReqHandler::handleRequest") << "Get Query params are empty.";
        }
                
        // TODO: we currently don't parse POST data.
        Poco::Net::NameValueCollection postParams;
        // Parse them here ...
        if(!postParams.empty())
        {
            callback->receivedVerifierCallbackPostParams(postParams);
        }
        else
        {
            ofLogVerbose("ofxOAuthAuthReqHandler::handleRequest") << "Post Query params are empty.";
        }

        std::string path = uri.getPath();

        if(isMatch(path,"/"))
        {
            path = "/index.html"; // default index
        }

        ofFile file(docRoot+path);
        ofBuffer outputBuffer;
        
        if(file.exists())
        {
            // text types
            std::string ext = file.getExtension();
            bool doReplacements = false;
            
            if(isMatch(ext, "html") || isMatch(ext, "htm"))
            {
                response.setContentType("text/html");
                doReplacements = true;
            }
            else if(isMatch(ext, "json"))
            {
                response.setContentType("application/json");
                // image types
            }
            else if(isMatch(ext, "jpg") || isMatch(ext, "jpeg") || isMatch(ext, "jpe"))
            {
                response.setContentType("image/jpeg");
            }
            else if(isMatch(ext, "png"))
            {
                response.setContentType("image/png");
            }
            else if(isMatch(ext, "gif"))
            {
                response.setContentType("image/gif");
            }
            else if(isMatch(ext, "ico"))
            {
                response.setContentType("image/vnd.microsoft.icon");

                // everything else
            }
            else
            {
                response.setContentType("text/html");
            }
            
        
            // replace any magic keys
            
            // {@QUERY} -> is replaced with URL
            // {@GET_PARAMS} -> is replaced with a params
            // {@POST_PARAMS} -> is replaced with post params
            // {@HEADERS} -> is replaced with headers
            // {@COOKIES} -> is replaced with cookies
            
            // load the file into the buffer
            file >> outputBuffer;
            
            if(doReplacements)
            {
                std::string text = outputBuffer.getText();
                
                std::string target;
                target = "{@QUERY}";
                Poco::replaceInPlace(text, target, makeHTMLList(uri.getQuery()));
                
                target = "{@GET_PARAMS}";
                Poco::replaceInPlace(text, target, makeHTMLList(queryParams));
                
                target = "{@POST_PARAMS}";
                Poco::replaceInPlace(text, target, makeHTMLList(postParams));

                target = "{@HEADERS}";
                Poco::replaceInPlace(text, target, makeHTMLList(request));
                
                target = "{@COOKIES}";
                Poco::replaceInPlace(text, target, makeHTMLList(cookies));

                outputBuffer.set(text);
            }
            
        }
        else
        {
            response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND,"Sorry, couldn't find it.");
            response.setContentType("text/html");

            ofFile file(docRoot + "/404.html");
            if(file.exists())
            {
                file >> outputBuffer;
            }
            else
            {
                std::string s = "<html><head><title>404</title></head><body><h1>404 - not found.</h1></body>";
                outputBuffer.set(s.c_str(),s.size());
            }
        }

        std::ostream& ostr = response.send();
        ostr << outputBuffer;
    }
    
protected:
    std::string makeHTMLList(const Poco::Net::NameValueCollection& params)
    {
        std::string html;
        html += "<ul>";
        for(Poco::Net::NameValueCollection::ConstIterator iter = params.begin();
            iter != params.end();
            iter++)
        {
            html += ("<li>" + (*iter).first + "=" + (*iter).second + "</li>");
        }

        html += "</ul>";

        return html;
    }
    
    std::string makeHTMLList(const std::string& value)
    {
        std::string html;
        html += "<ul>";
        html += ("<li>" + value + "</li>");
        html += "</ul>";
        return html;
    }

    
    bool parseQuery(const std::string& query,
                    Poco::Net::NameValueCollection& returnParams)
    {
        if(!query.empty())
        {
            // could use oauth_split_url_parameters here.
            std::vector<std::string> params = ofSplitString(query, "&", true);
            for(int i = 0; i < params.size(); i++)
            {
                std::vector<std::string> tokens = ofSplitString(params[i], "=");
                if(tokens.size() == 2)
                {
                    returnParams.set(tokens[0], tokens[1]);
                }
                else
                {
                    ofLogWarning("ofxOAuthAuthReqHandler::parseQuery") << "Return parameter did not have 2 values: " << ofToString(params[i]) << " - skipping.";
                }
            }
        }

        return !returnParams.empty();
    }
    
    bool isMatch (std::string const& s0, std::string const& s1)
    {
        return Poco::icompare(s0,s1) == 0;
    }

    ofxOAuthVerifierCallbackInterface* callback;

    std::string docRoot;
    
};


class ofxOAuthAuthReqHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory
{
public:
    ofxOAuthAuthReqHandlerFactory(ofxOAuthVerifierCallbackInterface* _callback,
                                  const std::string& _docRoot):
        callback(_callback),
        docRoot(_docRoot)
    {
    }

    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request)
    {
        return new ofxOAuthAuthReqHandler(callback, docRoot); 
    }

protected:

    ofxOAuthVerifierCallbackInterface* callback;
    std::string docRoot;

};


class ofxOAuthVerifierCallbackServer: public ofThread
{
public:
    ofxOAuthVerifierCallbackServer(ofxOAuthVerifierCallbackInterface* callback,
                                   const string& docRoot = "",
                                   int port = -1):
        _callback(callback),
        _docRoot(docRoot)
    {
        _port = port <= 0 ? (int)ofRandom(8000, 9000) : port;
    }
   
    virtual ~ofxOAuthVerifierCallbackServer()
    {
        waitForThread(true); // just in case
        ofLogVerbose("ofxOAuthVerifierCallbackServer::~ofxOAuthVerifierCallbackServer") << "Server destroyed.";

    }

    void start()
    {
        startThread(true);
    }

    void stop()
    {
        stopThread();
    }

    void threadedFunction()
    {
        ofLogVerbose("ofxOAuthVerifierCallbackServer::~ofxOAuthVerifierCallbackServer") << "Server starting @ " << getURL();

        Poco::Net::ServerSocket socket(_port);
        // all of these params are an attempt to make the server shut down VERY quickly.
        Poco::Net::HTTPServerParams* pParams = new Poco::Net::HTTPServerParams();

        pParams->setMaxQueued(1);
        pParams->setMaxThreads(1);
        pParams->setKeepAlive(false);
        pParams->setMaxKeepAliveRequests(0);
        pParams->setKeepAliveTimeout(1);
        pParams->setServerName("ofxOAuthVerifierCallbackServer/1.0");

        Poco::ThreadPool babyPool(1,1,1,1);
        Poco::Net::HTTPServer server(new ofxOAuthAuthReqHandlerFactory(_callback, _docRoot),
                                     babyPool,
                                     socket,
                                     new Poco::Net::HTTPServerParams());

        server.start(); // start the http server
        ofLogVerbose("ofxOAuthVerifierCallbackServer::~ofxOAuthVerifierCallbackServer") << "Server successfully started @ " + getURL();

        while( isThreadRunning() != 0 ) sleep(250);

        server.stop(); // stop the http server
        socket.close();
        babyPool.joinAll();

        ofLogVerbose("ofxOAuthVerifierCallbackServer::~ofxOAuthVerifierCallbackServer") << "Server successfully shut down.";
    }

    std::string getURL() const
    {
        return "http://127.0.0.1:" + ofToString(_port) + "/";
    }

    int getPort() const
    {
        return _port;
    }

    void setPort(int port)
    {
        _port = port;
    }

    void setDocRoot(const std::string& docRoot)
    {
        _docRoot = docRoot;
    }
    
protected:
    ofxOAuthVerifierCallbackInterface* _callback;
    int _port;
    std::string _docRoot;

};
