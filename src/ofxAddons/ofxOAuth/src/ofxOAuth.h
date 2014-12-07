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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <oauth.h>
#include "Poco/String.h"
#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxOAuthVerifierCallbackServer.h"
#include "ofxOAuthVerifierCallbackInterface.h"


class ofxOAuth: public ofxOAuthVerifierCallbackInterface
{
public:
    enum AuthMethod
    {
        OFX_OA_HMAC=0,
        OFX_OA_RSA,
        OFX_OA_PLAINTEXT
    };

    enum AuthHttpMethod
    {
        OFX_HTTP_GET,
        OFX_HTTP_POST
    };

    ofxOAuth();

    virtual ~ofxOAuth();

    void setup();

    void setup(const std::string& apiURL,
               const std::string& consumerKey,
               const std::string& consumerSecret);
    
    void setup(const std::string& apiURL,
               const std::string& requestTokenUrl,
               const std::string& accessTokenUrl,
               const std::string& authorizeUrl,
               const std::string& consumerKey,
               const std::string& consumerSecret);

    void update(ofEventArgs& args);
    
    bool isAuthorized();

    std::string get(const std::string& uri,
                    const std::string& queryParams = "");

    std::string post(const std::string& uri,
                     const std::string& queryParams = "");
    
    std::string postfile_multipartdata(const std::string& uri,
                     const std::string& queryParams = "",
                     const std::string& filefieldname = "",
                     const std::string& filepath = "");
    
    // getters and setters
    std::string getApiURL();
    void setApiURL(const std::string& v, bool autoSetEndpoints = true);
    
    std::string getRequestTokenURL();
    void setRequestTokenURL(const std::string& v);
    std::string getAccessTokenURL();
    void setAccessTokenURL(const std::string& v);
    std::string getAuthorizationURL();
    void setAuthorizationURL(const std::string& v);
    std::string getVerifierCallbackURL();
    void setVerifierCallbackURL(const std::string& v);

    void setApplicationDisplayName(const std::string& v); // xoauth_displayname
    std::string getApplicationDisplayName();
    
    void setApplicationScope(const std::string& v); // google specific
    std::string getApplicationScope();
    
    // verifier callback server
    void setEnableVerifierCallbackServer(bool v);
    bool isVerifierCallbackServerEnabled();
    
    void setVerifierCallbackServerDocRoot(const std::string& docRoot);
    std::string getVerifierCallbackServerDocRoot();
    
    bool isVerifierCallbackPortSet() const;
    int getVerifierCallbackServerPort() const;
    void setVerifierCallbackServerPort(int portNumber);

    
    // request token / secret
    std::string getRequestToken();
    void setRequestToken(const std::string& v);
    std::string getRequestTokenSecret();
    void setRequestTokenSecret(const string& v);
    std::string getRequestTokenVerifier();
    void setRequestTokenVerifier(const std::string& requestToken,
                                 const std::string& requestTokenVerifier);
    void setRequestTokenVerifier(const std::string& requestTokenVerifier);

    // request access token / secret
    std::string getAccessToken();
    void setAccessToken(const std::string& v);
    std::string getAccessTokenSecret();
    void setAccessTokenSecret(const std::string& v);

    std::string getScreenName();
    void setScreenName(const std::string& v);
    
    std::string getEncodedUserId();
    void setEncodedUserId(const std::string& v);

    std::string getUserId();
    void setUserId(const std::string& v);
    
    std::string getEncodedUserPassword();
    void setEncodedUserPassword(const std::string& v);

    std::string getUserPassword();
    void setUserPassword(const std::string& v);
    
    // request consumer token / secret
    std::string getConsumerKey() const;
    void setConsumerKey(const std::string& v);
    std::string getConsumerSecret() const;
    void setConsumerSecret(const std::string& v);
    
    void setApiName(const std::string& v);
    std::string getApiName() const;

    std::map<std::string, std::string> getCustomInfo() const;

    // token verifier
    std::string getRealm() const;
    void setRealm(const std::string& v);
    
    
    void setSSLCACertificateFile(const std::string& pathname);
    
    
    void setCredentialsPathname(const std::string& credentials);
    std::string getCredentialsPathname();
    
    void resetErrors();
    
protected:
    
    void saveCredentials();
    void loadCredentials();

    AuthMethod getOAuthMethod();
    void setOAuthMethod(AuthMethod v);

    std::map<std::string,std::string> obtainRequestToken();
    std::map<std::string,std::string> obtainAccessToken();
    
    std::string requestUserVerification(bool launchBrowser = true);
    std::string requestUserVerification(std::string additionalAuthParams,
                                        bool launchBrowser = true);

    
    std::string credentialsPathname;
    
    // URLS
    std::string apiURL;
    
    std::string requestTokenURL;
    std::string accessTokenURL;
    std::string authorizationURL;
    std::string verifierCallbackURL;

    std::string applicationDisplayName;
    std::string applicationScope;
    
    bool callbackConfirmed;
    bool verificationRequested;
    bool accessFailed;
    bool accessFailedReported;
    
    // keys, secrets and verifiers
    
    std::string consumerKey;    // provided by the api for each app
    std::string consumerSecret; // provided by the api for each app
    
    std::string requestToken;         // initially acquired via obtainRequestToken()
    std::string requestTokenSecret;   // initially acquired via obtainRequestToken()
    std::string requestTokenVerifier;      // acquired via web server callback or manual entry by user

    // the following
    std::string apiName;
    std::string accessToken;          // after requestToken, requestTokenSecret and requestVerifier,
    std::string accessTokenSecret;
    std::string encodedUserId;

    std::string screenName;
    std::string userId;
    std::string encodedUserPassword;
    std::string userPassword;


    // for dta such as screenName, userId, encodedUserPassword, userPassword, etc.
    std::map<std::string, std::string> customInfo;

    // other stuff
    
    std::string realm;
    AuthMethod oauthMethod;
    AuthHttpMethod httpMethod;
    // where is our ssl cert bundles stored?
    std::string SSLCACertificateFile;

    // authorization callback server
    bool enableVerifierCallbackServer;
    std::shared_ptr<ofxOAuthVerifierCallbackServer> verifierCallbackServer;
    std::string verifierCallbackServerDocRoot;
    int vertifierCallbackServerPort;

    // callbacks from the webserver
    void receivedVerifierCallbackRequest(const Poco::Net::HTTPServerRequest& request);
    void receivedVerifierCallbackHeaders(const Poco::Net::NameValueCollection& headers);
    void receivedVerifierCallbackCookies(const Poco::Net::NameValueCollection& cookies);
    void receivedVerifierCallbackGetParams(const Poco::Net::NameValueCollection& getParams);
    void receivedVerifierCallbackPostParams(const Poco::Net::NameValueCollection& postParams);

    std::string appendQuestionMark(const std::string& url) const;

private:
    OAuthMethod _getOAuthMethod();
    std::string _getHttpMethod();

    std::string _old_curlopt_cainfo; 
    
};
