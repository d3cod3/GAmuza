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


#include "ofxOAuth.h"

#define HAVE_CURL 1

#ifdef HAVE_CURL /* HTTP requests via libcurl */
//#include "xmalloc.h"

#define VERSION 1.0.0

#define OAUTH_USER_AGENT "liboauth-agent/1.0.1"

#include <curl/curl.h>
#include <sys/stat.h>

#define GLOBAL_CURL_ENVIROMENT_OPTIONS \
if (getenv("CURLOPT_PROXYAUTH")){ \
curl_easy_setopt(curl, CURLOPT_PROXYAUTH, CURLAUTH_ANY); \
cout << "CURLOPT_PROXYAUTH: " << getenv("CURLOPT_PROXYAUTH") << endl; \
} \
if (getenv("CURLOPT_SSL_VERIFYPEER")){ \
curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, (long) atol(getenv("CURLOPT_SSL_VERIFYPEER")) ); \
cout << "CURLOPT_SSL_VERIFYPEER: " << getenv("CURLOPT_SSL_VERIFYPEER") << endl; \
} \
if (getenv("CURLOPT_CAINFO")){ \
curl_easy_setopt(curl, CURLOPT_CAINFO, getenv("CURLOPT_CAINFO") ); \
cout << "CURLOPT_CAINFO: " << getenv("CURLOPT_CAINFO") << endl; \
} \
if (getenv("CURLOPT_FOLLOWLOCATION")){ \
curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, (long) atol(getenv("CURLOPT_FOLLOWLOCATION")) ); \
cout << "CURLOPT_FOLLOWLOCATION: " << getenv("CURLOPT_FOLLOWLOCATION") << endl; \
} \
if (getenv("CURLOPT_FAILONERROR")){ \
curl_easy_setopt(curl, CURLOPT_FAILONERROR, (long) atol(getenv("CURLOPT_FAILONERROR")) ); \
cout << "CURLOPT_FAILONERROR: " << getenv("CURLOPT_FAILONERROR") << endl; \
}

struct MemoryStruct
{
    char* data;
    std::size_t size; //< bytes remaining (r), bytes accumulated (w)
    std::size_t start_size; //< only used with ..AndCall()
    void (*callback)(void*,
                     int,
                     std::size_t,
                     std::size_t); //< only used with ..AndCall()
    void* callback_data; //< only used with ..AndCall()
};

static std::size_t WriteMemoryCallback(void* ptr,
                                       std::size_t size,
                                       std::size_t nmemb,
                                       void* data)
{
    std::stringstream ss;
    ss << "IN MEMORY CALLBACK" << endl;
    ss << "ptr: " << ptr << endl;
    ss << "size: " << size << endl;
    ss << "nmemb: " << nmemb << endl;
    ss << "data: " << data << endl;

    std::size_t realsize = size * nmemb;

    struct MemoryStruct *mem = (struct MemoryStruct *)data;

    mem->data = (char*)realloc(mem->data, mem->size + realsize + 1);

    if (mem->data)
    {
        memcpy(&(mem->data[mem->size]), ptr, realsize);
        mem->size += realsize;
        mem->data[mem->size] = 0;
    }

    ss << "----" << endl;
    ss << "ptr: " << ptr << endl;
    ss << "size: " << size << endl;
    ss << "nmemb: " << nmemb << endl;
    ss << "data: " << data << endl;
    ss << "realsize: " << realsize << endl;

    ofLogVerbose("WriteMemoryCallback") << ss.str();

    return realsize;
}

static std::size_t ReadMemoryCallback(void*ptr,
                                      std::size_t size,
                                      std::size_t nmemb,
                                      void*data)
{
    struct MemoryStruct *mem = (struct MemoryStruct *)data;
    std::size_t realsize = size * nmemb;
    if (realsize > mem->size) realsize = mem->size;
    memcpy(ptr, mem->data, realsize);
    mem->size -= realsize;
    mem->data += realsize;
    return realsize;
}

static std::size_t WriteMemoryCallbackAndCall(void* ptr,
                                              std::size_t size,
                                              std::size_t nmemb,
                                              void* data)
{
    struct MemoryStruct *mem = (struct MemoryStruct *)data;
    std::size_t ret=WriteMemoryCallback(ptr,size,nmemb,data);
    mem->callback(mem->callback_data, 0, mem->size, mem->size);
    return ret;
}

static size_t ReadMemoryCallbackAndCall(void*ptr,
                                        std::size_t size,
                                        std::size_t nmemb,
                                        void*data)
{
    struct MemoryStruct *mem = (struct MemoryStruct *)data;
    std::size_t ret=ReadMemoryCallback(ptr,size,nmemb,data);
    mem->callback(mem->callback_data,
                  1,
                  mem->start_size-mem->size,
                  mem->start_size);
    return ret;
}

/**
 * cURL http post function.
 * the returned string (if not NULL) needs to be freed by the caller
 *
 * @param u url to retrieve
 * @param p post parameters
 * @param customheader specify custom HTTP header (or NULL for none)
 * @return returned HTTP
 */
char *ofx_oauth_curl_post (const char *u, const char *p, const char *customheader) {
     CURL *curl;
     CURLcode res;
     struct curl_slist *slist=NULL;

     struct MemoryStruct chunk;
     chunk.data=NULL;
     chunk.size = 0;

    curl = curl_easy_init();
    if(!curl) return NULL;
    curl_easy_setopt(curl, CURLOPT_URL, u);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, p);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    if (customheader) {
        slist = curl_slist_append(slist, customheader);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
    }
    curl_easy_setopt(curl, CURLOPT_USERAGENT, OAUTH_USER_AGENT);
#ifdef OAUTH_CURL_TIMEOUT
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, OAUTH_CURL_TIMEOUT);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
#endif
    GLOBAL_CURL_ENVIROMENT_OPTIONS;
    res = curl_easy_perform(curl);
    curl_slist_free_all(slist);
    if (res) {
        return NULL;
    }

     curl_easy_cleanup(curl);
     return (chunk.data);
}

/**
 * cURL http get function.
 * the returned string (if not NULL) needs to be freed by the caller
 *
 * @param u url to retrieve
 * @param q optional query parameters
 * @param customheader specify custom HTTP header (or NULL for none)
 * @return returned HTTP
 */
char *ofx_oauth_curl_get (const char *u,
                          const char *q,
                          const char *customheader,
                          const char* SSLCACertificateFile)
{
    CURL *curl;
    CURLcode res;
    struct curl_slist *slist=NULL;
    char *t1=NULL;
    struct MemoryStruct chunk;

    if (q) {
        t1=(char*)malloc(sizeof(char)*(strlen(u)+strlen(q)+2));
        strcpy(t1,u); strcat(t1,"?"); strcat(t1,q);
    }

    chunk.data=NULL;
    chunk.size = 0;

    curl = curl_easy_init();
    if(!curl) {
        ofLogError() << "CURL WAS NOT INITIALIZED";
        return NULL;
    }

    // GLOBAL_CURL_ENVIROMENT_OPTIONS;

//    cout << "URL TO CHECK " << (q ? t1:u) << endl;

    curl_easy_setopt(curl, CURLOPT_URL, q ? t1:u);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    if (customheader) 
    {
        slist = curl_slist_append(slist, customheader);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
    }
// #if 0 // TODO - support request methods..
//     if (0)
//         curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "HEAD");
//     else if (0)
//         curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
// #endif
    curl_easy_setopt(curl, CURLOPT_USERAGENT, OAUTH_USER_AGENT);
// #ifdef OAUTH_CURL_TIMEOUT
    // curl_easy_setopt(curl, CURLOPT_TIMEOUT, OAUTH_CURL_TIMEOUT);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
// #endif
    // GLOBAL_CURL_ENVIROMENT_OPTIONS;

    char errorBuffer[1024];

    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);

// THIS IS A BAD INSECURE WORKAROUND BECAUSE curl on linux64 isn't cooperating ...
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER , FALSE);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST , FALSE);

    curl_easy_setopt(curl, CURLOPT_CAINFO , SSLCACertificateFile);

    ofLogVerbose() << "SSLCACertificateFile: " << SSLCACertificateFile << endl;

    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

    // if (getenv("CURLOPT_CAINFO"))
    // { 
        // curl_easy_setopt(curl, CURLOPT_CAINFO, getenv("CURLOPT_CAINFO") ); 
    //     // cout << "CURLOPT_CAINFO: " << getenv("CURLOPT_CAINFO") << endl; \
    // }   



    res = curl_easy_perform(curl);
    curl_slist_free_all(slist);

    if(strlen(errorBuffer) > 0)
    {
        cout << "ERROR: "<< errorBuffer << endl;
    }


    if (q)
    {
        free(t1);
    }

    curl_easy_cleanup(curl);

    if (res)
    {
        ofLogVerbose() << "CURL RETURNED NOTHING";
        return NULL;
    }

    ofLogVerbose() << "CURL RETURNED THIS: " << chunk.data;

    return (chunk.data);
}

/**
 * cURL http post raw data from file.
 * the returned string needs to be freed by the caller
 *
 * @param u url to retrieve
 * @param fn filename of the file to post along
 * @param len length of the file in bytes. set to '0' for autodetection
 * @param customheader specify custom HTTP header (or NULL for default)
 * @return returned HTTP or NULL on error
 */
char *ofx_oauth_curl_post_file (const char *u, const char *fn, size_t len, const char *customheader) {
    CURL *curl;
    CURLcode res;
    struct curl_slist *slist=NULL;
    struct MemoryStruct chunk;
    FILE *f;

    chunk.data=NULL;
    chunk.size=0;

    if (customheader)
        slist = curl_slist_append(slist, customheader);
    else
        slist = curl_slist_append(slist, "Content-Type: image/jpeg;");

    if (!len) {
        struct stat statbuf;
        if (stat(fn, &statbuf) == -1) return(NULL);
        len = statbuf.st_size;
    }

    f = fopen(fn,"r");
    if (!f) return NULL;

    curl = curl_easy_init();
    if(!curl) return NULL;
    curl_easy_setopt(curl, CURLOPT_URL, u);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, len);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
    curl_easy_setopt(curl, CURLOPT_READDATA, f);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, OAUTH_USER_AGENT);
#ifdef OAUTH_CURL_TIMEOUT
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, OAUTH_CURL_TIMEOUT);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
#endif
    GLOBAL_CURL_ENVIROMENT_OPTIONS;
    res = curl_easy_perform(curl);
    curl_slist_free_all(slist);
    if (res) {
        // error
        return NULL;
    }
    fclose(f);
     curl_easy_cleanup(curl);
     return (chunk.data);
}


/**
 * cURL http post raw raw data from file with multipartformdata
 * the returned string needs to be freed by the caller
 *
 * @param u url to retrieve
 * @param p post parameters
 * @param pc post parameters count
 * @param ffn name of the field that holds file data on the form
 * @param fn filename of the file to post along
 * @param len length of the file in bytes. set to '0' for autodetection
 * @param customheader specify custom HTTP header (or NULL for default)
 * @return returned HTTP or NULL on error
 */
char *ofx_oauth_curl_post_file_multipartformdata(const char *u, const std::string q, const char *ffn, const char *fn, size_t len, const char *customheader) {
   
    CURL *curl;
    CURLcode res;
    struct curl_slist *slist=NULL;
    struct MemoryStruct chunk;
    
    chunk.data=NULL;
    chunk.size=0;
    
    if (customheader)
        slist = curl_slist_append(slist, customheader);
    
    if (!len) {
        struct stat statbuf;
        if (stat(fn, &statbuf) == -1) return(NULL);
        len = statbuf.st_size;
    }
    
    struct curl_httppost* post = NULL;
    struct curl_httppost* last = NULL;
    struct curl_forms forms[2];
    
    // TODO: Maybe we can implement multiple file post here:
    forms[0].option = CURLFORM_FILE;
    forms[0].value = fn;
    forms[1].option = CURLFORM_END;
    
    /* Fill in the file upload field. This makes libcurl load data from
     the given file name when curl_easy_perform() is called. */

    curl_formadd(&post,
                  &last,
                  CURLFORM_COPYNAME, ffn,
                  CURLFORM_ARRAY, forms,
                  CURLFORM_END);
    
    /* Fill in other fields */

    char * cstr = new char [q.length()+1];
    std::strcpy (cstr, q.c_str());
    char * p = std::strtok (cstr,"&");
    while (p!=0)
    {
        string line(p);
        unsigned int pos = line.find("=");
        string arr[2];
        arr[0] = line.substr(0,pos);
        arr[1] = line.substr(pos+1,line.length());
        curl_formadd(&post,
                    &last,
                     CURLFORM_COPYNAME, arr[0].c_str(),
                     CURLFORM_COPYCONTENTS, arr[1].c_str(),
                     CURLFORM_END);
        p = strtok(NULL," ");
    }
    delete[] cstr;
    
    curl = curl_easy_init();
    if(!curl) return NULL;
    
    curl_easy_setopt(curl, CURLOPT_URL, u);
    curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, OAUTH_USER_AGENT);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, len);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    // Debug info:
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    //curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
#ifdef OAUTH_CURL_TIMEOUT
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, OAUTH_CURL_TIMEOUT);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
#endif
    GLOBAL_CURL_ENVIROMENT_OPTIONS;
    res = curl_easy_perform(curl);
    curl_slist_free_all(slist);
    if (res) {
        // error
        return NULL;
    }
    
    curl_easy_cleanup(curl);
    return (chunk.data);
    
}

/**
 * http send raw data, with callback.
 * the returned string needs to be freed by the caller
 *
 * more documentation in oauth.h
 *
 * @param u url to retrieve
 * @param data data to post along
 * @param len length of the file in bytes. set to '0' for autodetection
 * @param customheader specify custom HTTP header (or NULL for default)
 * @param callback specify the callback function
 * @param callback_data specify data to pass to the callback function
 * @return returned HTTP reply or NULL on error
 */
char *ofx_oauth_curl_send_data_with_callback (const char *u, const char *data, size_t len, const char *customheader, void (*callback)(void*,int,size_t,size_t), void*callback_data, const char *httpMethod) {
    CURL *curl;
    CURLcode res;
    struct curl_slist *slist=NULL;
    struct MemoryStruct chunk;
    struct MemoryStruct rdnfo;

    chunk.data=NULL;
    chunk.size=0;
    chunk.start_size=0;
    chunk.callback=callback;
    chunk.callback_data=callback_data;
    rdnfo.data=(char *)data;
    rdnfo.size=len;
    rdnfo.start_size=len;
    rdnfo.callback=callback;
    rdnfo.callback_data=callback_data;

    if (customheader)
        slist = curl_slist_append(slist, customheader);
    else
        slist = curl_slist_append(slist, "Content-Type: image/jpeg;");

    curl = curl_easy_init();
    if(!curl) return NULL;
    curl_easy_setopt(curl, CURLOPT_URL, u);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    if (httpMethod) curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, httpMethod);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, len);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
    curl_easy_setopt(curl, CURLOPT_READDATA, (void*)&rdnfo);
    if (callback)
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, ReadMemoryCallbackAndCall);
    else
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, ReadMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
    if (callback)
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallbackAndCall);
    else
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, OAUTH_USER_AGENT);
#ifdef OAUTH_CURL_TIMEOUT
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, OAUTH_CURL_TIMEOUT);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
#endif
    GLOBAL_CURL_ENVIROMENT_OPTIONS;
    res = curl_easy_perform(curl);
    curl_slist_free_all(slist);
    if (res) {
        // error
        return NULL;
    }

    curl_easy_cleanup(curl);
    return (chunk.data);
}

/**
 * http post raw data.
 * the returned string needs to be freed by the caller
 *
 * more documentation in oauth.h
 *
 * @param u url to retrieve
 * @param data data to post along
 * @param len length of the file in bytes. set to '0' for autodetection
 * @param customheader specify custom HTTP header (or NULL for default)
 * @return returned HTTP reply or NULL on error
 */
// char *ofx_oauth_curl_post_data(const char *u, const char *data, size_t len, const char *customheader) {
//     return ofx_oauth_curl_send_data_with_callback(u, data, len, customheader, NULL, NULL, NULL);
// }

// char *ofx_oauth_curl_send_data (const char *u, const char *data, size_t len, const char *customheader, const char *httpMethod) {
//     return ofx_oauth_curl_send_data_with_callback(u, data, len, customheader, NULL, NULL, httpMethod);
// }

char *ofx_oauth_curl_post_data_with_callback (const char *u, const char *data, size_t len, const char *customheader, void (*callback)(void*,int,size_t,size_t), void*callback_data) {
    return ofx_oauth_curl_send_data_with_callback(u, data, len, customheader, callback, callback_data, NULL);
}

/**
 * do a HTTP GET request, wait for it to finish
 * and return the content of the reply.
 * (requires libcurl)
 *
 * @param u base url to get
 * @param q query string to send along with the HTTP request or NULL.
 * @param customheader specify custom HTTP header (or NULL for none)
 * @return  In case of an error NULL is returned; otherwise a pointer to the
 * replied content from HTTP server. latter needs to be freed by caller.
 */
char *ofx_oauth_http_get2 (const char *u, const char *q, const char *customheader,const char* SSLCACertificateFile) {
#ifdef HAVE_CURL

    ofLogVerbose() << "==================THIS IS THE INSIDE OF THE THE FUNCTION ";

    return ofx_oauth_curl_get(u,q,customheader,SSLCACertificateFile);
#else
    return NULL;
#endif
}

#endif // libcURL.



ofxOAuth::ofxOAuth(): ofxOAuthVerifierCallbackInterface()
{
    oauthMethod = OFX_OA_HMAC;  // default
    httpMethod  = OFX_HTTP_GET; // default

    const char* v = getenv("CURLOPT_CAINFO");
    
    if(0 != v) _old_curlopt_cainfo = v;

    // this Certificate Authority bundle is extracted 
    // from mozilla.org.pem, which can be found here
    //
    // http://curl.haxx.se/ca/
    // http://curl.haxx.se/ca/cacert.pem
    //
    // If it is not placed in the default (PROJECT)/data/
    // directory, an different location can 
    // can be set by calling:
    
    // cout << "OLD_CURLOPT_CAINFO" << getenv("CURLOPT_CAINFO") << endl;

    // setSSLCACertificateFile("cacert.pem");
    setSSLCACertificateFile("certdata.txt");

    // cout << "NEW_CURLOPT_CAINFO" << getenv("CURLOPT_CAINFO") << endl;
    
    // this setter sets an environmental variable,
    // which is accessed by liboauth whenever libcurl
    // calls are executed.
    
    callbackConfirmed = false;
    
    verificationRequested = false;
    accessFailed = false;
    accessFailedReported = false;
    
    apiName = "GENERIC"; 
    
    credentialsPathname = "credentials.xml";
    verifierCallbackServerDocRoot = "VerifierCallbackServer/";
    vertifierCallbackServerPort = -1;
    enableVerifierCallbackServer = true;
    
    ofAddListener(ofEvents().update,this,&ofxOAuth::update);
}


ofxOAuth::~ofxOAuth()
{
    // be nice and set it back, if there was 
    // something there when we started.
    // if(!_old_curlopt_cainfo.empty())
    // {
    //     setenv("CURLOPT_CAINFO",_old_curlopt_cainfo.c_str(),true);
    // }
    // else
    // {
    //     unsetenv("CURLOPT_CAINFO");
    // }

    ofRemoveListener(ofEvents().update,this,&ofxOAuth::update);
}


void ofxOAuth::setup()
{
    loadCredentials();
}

//------------------------------------------------------------------------------
void ofxOAuth::setup(const std::string& _apiURL,
                     const std::string& _requestTokenUrl,
                     const std::string& _accessTokenUrl,
                     const std::string& _authorizeUrl,
                     const std::string& _consumerKey,
                     const std::string& _consumerSecret)
{
    setApiURL(_apiURL,false);
    setRequestTokenURL(_requestTokenUrl);
    setAccessTokenURL(_accessTokenUrl);
    setAuthorizationURL(_authorizeUrl);
    setConsumerKey(_consumerKey);
    setConsumerSecret(_consumerSecret);

    loadCredentials();
}


void ofxOAuth::setup(const std::string& _apiURL,
                     const std::string& _consumerKey,
                     const std::string& _consumerSecret)
{
    setApiURL(_apiURL);
    setConsumerKey(_consumerKey);
    setConsumerSecret(_consumerSecret);

    loadCredentials();
}


void ofxOAuth::update(ofEventArgs& args)
{
    if(accessFailed)
    {
        if(!accessFailedReported)
        {
            ofLogError("ofxOAuth::update") << "Access failed.";
            accessFailedReported = true;
        }
    }
    else if(accessToken.empty() || accessTokenSecret.empty())
    {
        if(requestTokenVerifier.empty())
        {
            if(requestToken.empty())
            {
                if(enableVerifierCallbackServer)
                {
                    if(0 == verifierCallbackServer)
                    {
                        verifierCallbackServer = std::shared_ptr<ofxOAuthVerifierCallbackServer>(new ofxOAuthVerifierCallbackServer(this,verifierCallbackServerDocRoot, vertifierCallbackServerPort));
                        verifierCallbackURL = verifierCallbackServer->getURL();
                        verifierCallbackServer->start();
                    }
                }
                else
                {
                    // nichts
                    ofLogVerbose("ofxOAuth::update") << "Server disabled, expecting verifiy key input via a non server method (i.e. text input.)";
                    ofLogVerbose("ofxOAuth::update") << "\t\tThis is done via 'oob' (Out-of-band OAuth authentication).";
                    ofLogVerbose("ofxOAuth::update") << "\t\tCall setRequestTokenVerifier() with a verification code to continue.";
                }

                obtainRequestToken();
            }
            else
            {
                if(!verificationRequested)
                {
                    requestUserVerification();
                    verificationRequested = true;
                    ofLogVerbose("ofxOAuth::update") << "Waiting for user verification (need the pin number / requestTokenVerifier!)";
                    ofLogVerbose("ofxOAuth::update") << "\t\tIf the server is enabled, then this will happen as soon as the user is redirected.";
                    ofLogVerbose("ofxOAuth::update") << "\t\tIf the server is disabled, verification must be done via 'oob'";
                    ofLogVerbose("ofxOAuth::update") << "\t\t(Out-of-band OAuth authentication). Call setRequestTokenVerifier()";
                    ofLogVerbose("ofxOAuth::update") << "\t\twith a verification code to continue.";
                }
                else
                {
                    // nichts
                }
            }
        }
        else
        {
            if(!accessFailed)
            {
                verificationRequested = false;
                if(0 != verifierCallbackServer)
                {
                    verifierCallbackServer->stop(); // stop the server
                    verifierCallbackServer.reset(); // destroy the server, setting it back to null
                }
                obtainAccessToken();
            }
        } 
    }
    else
    {
        if(0 != verifierCallbackServer)
        {
            // go ahead and free that memory
            verifierCallbackServer->stop(); // stop the server
            verifierCallbackServer.reset(); // destroy the server, setting it back to null
        }
    }
}


std::string ofxOAuth::get(const std::string& uri, const std::string& query)
{
    std::string result = "";
        
    if(apiURL.empty())
    {
        ofLogError("ofxOAuth::get") << "No api URL specified.";
        return result;
    }
    
    if(consumerKey.empty())
    {
        ofLogError("ofxOAuth::get") << "No consumer key specified.";
        return result;
    }
    
    if(consumerSecret.empty())
    {
        ofLogError("ofxOAuth::get") << "No consumer secret specified.";
        return result;
    }
    
    if(accessToken.empty())
    {
        ofLogError("ofxOAuth::get") << "No access token specified.";
        return result;
    }

    if(accessTokenSecret.empty())
    {
        ofLogError("ofxOAuth::get") << "No access token secret specified.";
        return result;
    }

    std::string req_url;
    std::string req_hdr;
    std::string http_hdr;
    
    std::string reply;
    
    // oauth_sign_url2 (see oauth.h) in steps
    int  argc   = 0;
    char **argv = 0;
    
    // break apart the url parameters to they can be signed below
    // if desired we can also pass in additional patermeters (like oath* params)
    // here.  For instance, if ?oauth_callback=XXX is defined in this url,
    // it will be parsed and used in the Authorization header.
    
    std::string url = apiURL + uri + "?" + query;
    
    argc = oauth_split_url_parameters(url.c_str(), &argv);
    
    // sign the array.
    oauth_sign_array2_process(&argc, 
                              &argv,
                              0, //< postargs (unused)
                              _getOAuthMethod(), // hash type, OA_HMAC, OA_RSA, OA_PLAINTEXT
                              _getHttpMethod().c_str(), //< HTTP method (defaults to "GET")
                              consumerKey.c_str(), //< consumer key - posted plain text
                              consumerSecret.c_str(), //< consumer secret - used as 1st part of secret-key
                              accessToken.c_str(),  //< token key - posted plain text in URL
                              accessTokenSecret.c_str()); //< token secret - used as 2st part of secret-key
    
    ofLogVerbose("ofxOAuth::get") << "-------------------";
    ofLogVerbose("ofxOAuth::get") << "consumerKey          >" << consumerKey << "<";
    ofLogVerbose("ofxOAuth::get") << "consumerSecret       >" << consumerSecret << "<";
    ofLogVerbose("ofxOAuth::get") << "requestToken         >" << requestToken << "<";
    ofLogVerbose("ofxOAuth::get") << "requestTokenVerifier >" << requestTokenVerifier << "<";
    ofLogVerbose("ofxOAuth::get") << "requestTokenSecret   >" << requestTokenSecret << "<";
    ofLogVerbose("ofxOAuth::get") << "accessToken          >" << accessToken << "<";
    ofLogVerbose("ofxOAuth::get") << "accessTokenSecret    >" << accessTokenSecret << "<";
    ofLogVerbose("ofxOAuth::get") << "-------------------";

    // collect any parameters in our list that need to be placed in the request URI
    char* p_req_url = oauth_serialize_url_sep(argc, 0, argv, const_cast<char *>("&"), 1);

    if(0 != p_req_url)
    {
        req_url = p_req_url;
        free(p_req_url);
    }

    // collect any of the oauth parameters for inclusion in the HTTP Authorization header.
    char* p_req_hdr = oauth_serialize_url_sep(argc, 1, argv, const_cast<char *>(", "), 6); // const_cast<char *>() is to avoid Deprecated

    if(0 != p_req_hdr)
    {
        req_hdr = p_req_hdr;
        free(p_req_hdr);
    }

    // look at url parameters to be signed if you want.
    if(ofGetLogLevel() <= OF_LOG_VERBOSE)
        for (int i=0;i<argc; i++) ofLogVerbose("ofxOAuth::get") << " : " << i << ":" << argv[i];
    
    // free our parameter arrays that were allocated during parsing above    
    oauth_free_array(&argc, &argv);
    
    // construct the Authorization header.  Include realm information if available.
    if(!realm.empty())
    {
        // Note that (optional) 'realm' is not to be 
        // included in the oauth signed parameters and thus only added here.
        // see 9.1.1 in http://oauth.net/core/1.0/#anchor14
        http_hdr = "Authorization: OAuth realm=\"" + realm + "\", " + req_hdr; 
    }
    else
    {
        http_hdr = "Authorization: OAuth " + req_hdr; 
    }
    
    ofLogVerbose("ofxOAuth::get") << "request URL    >" << req_url << "<";
    ofLogVerbose("ofxOAuth::get") << "request HEADER >" << req_hdr << "<";
    ofLogVerbose("ofxOAuth::get") << "http    HEADER >" << http_hdr << "<";

    char* p_reply = ofx_oauth_http_get2(req_url.c_str(),   // the base url to get
                                        0,              // the query string to send
                                        http_hdr.c_str(),
                                        SSLCACertificateFile.c_str()); // Authorization header is included here

    if(0 != p_reply)
    {
        reply = p_reply;
        free(p_reply);
    }

    if (reply.empty())
    {
        ofLogVerbose("ofxOAuth::get") << "HTTP get request failed.";
    }
    else
    {
        ofLogVerbose("ofxOAuth::get") << "HTTP-Reply: " << reply;
        result = reply;
    }
    
    return result;
}


std::string ofxOAuth::post(const std::string& uri, const std::string& query)
{
    
    std::string result = "";
    
    if(apiURL.empty())
    {
        ofLogError("ofxOAuth::post") << "No api URL specified.";
        return result;
    }
    
    if(consumerKey.empty())
    {
        ofLogError("ofxOAuth::post") << "No consumer key specified.";
        return result;
    }
    
    if(consumerSecret.empty())
    {
        ofLogError("ofxOAuth::post") << "No consumer secret specified.";
        return result;
    }
    
    if(accessToken.empty())
    {
        ofLogError("ofxOAuth::post") << "No access token specified.";
        return result;
    }
    
    if(accessTokenSecret.empty())
    {
        ofLogError("ofxOAuth::post") << "No access token secret specified.";
        return result;
    }
    
    std::string req_url;
    std::string req_hdr;
    std::string http_hdr;
    
    std::string reply;
    
    // oauth_sign_url2 (see oauth.h) in steps
    int  argc   = 0;
    char **argv = 0;
    
    // break apart the url parameters to they can be signed below
    // if desired we can also pass in additional patermeters (like oath* params)
    // here.  For instance, if ?oauth_callback=XXX is defined in this url,
    // it will be parsed and used in the Authorization header.
    
    std::string url = apiURL + uri + "?" + query;
    
    argc = oauth_split_url_parameters(url.c_str(), &argv);
    
    // sign the array.
    oauth_sign_array2_process(&argc,
                              &argv,
                              0, //< postargs (unused)
                              _getOAuthMethod(), // hash type, OA_HMAC, OA_RSA, OA_PLAINTEXT
                              "POST", //< HTTP method (defaults to "GET")
                              consumerKey.c_str(), //< consumer key - posted plain text
                              consumerSecret.c_str(), //< consumer secret - used as 1st part of secret-key
                              accessToken.c_str(),  //< token key - posted plain text in URL
                              accessTokenSecret.c_str()); //< token secret - used as 2st part of secret-key
    
    ofLogVerbose("ofxOAuth::post") << "-------------------";
    ofLogVerbose("ofxOAuth::post") << "consumerKey          >" << consumerKey << "<";
    ofLogVerbose("ofxOAuth::post") << "consumerSecret       >" << consumerSecret << "<";
    ofLogVerbose("ofxOAuth::post") << "requestToken         >" << requestToken << "<";
    ofLogVerbose("ofxOAuth::post") << "requestTokenVerifier >" << requestTokenVerifier << "<";
    ofLogVerbose("ofxOAuth::post") << "requestTokenSecret   >" << requestTokenSecret << "<";
    ofLogVerbose("ofxOAuth::post") << "accessToken          >" << accessToken << "<";
    ofLogVerbose("ofxOAuth::post") << "accessTokenSecret    >" << accessTokenSecret << "<";
    ofLogVerbose("ofxOAuth::post") << "-------------------";
    
    // collect any parameters in our list that need to be placed as post params
    char *post_params = oauth_serialize_url_sep(argc, 1, argv, const_cast<char *>("&"), 1);
    
    req_url =  apiURL + uri;

    // collect any of the oauth parameters for inclusion in the HTTP Authorization header.
    char* p_req_hdr = oauth_serialize_url_sep(argc, 1, argv, const_cast<char *>(", "), 2); // const_cast<char *>() is to avoid Deprecated
    
    if(0 != p_req_hdr)
    {
        req_hdr = p_req_hdr;
        free(p_req_hdr);
    }
    
    // look at url parameters to be signed if you want.
    if(ofGetLogLevel() <= OF_LOG_VERBOSE)
        for (int i=0;i<argc; i++) ofLogVerbose("ofxOAuth::post") << " : " << i << ":" << argv[i];
    
    // free our parameter arrays that were allocated during parsing above
    oauth_free_array(&argc, &argv);
    
    // construct the Authorization header.  Include realm information if available.
    if(!realm.empty())
    {
        // Note that (optional) 'realm' is not to be
        // included in the oauth signed parameters and thus only added here.
        // see 9.1.1 in http://oauth.net/core/1.0/#anchor14
        http_hdr = "Authorization: OAuth realm=\"" + realm + "\", " + req_hdr;
    }
    else
    {
        http_hdr = "Authorization: OAuth " + req_hdr;
    }
    
    ofLogVerbose("ofxOAuth::post") << "request URL    >" << req_url << "<";
    ofLogVerbose("ofxOAuth::post") << "request HEADER >" << req_hdr << "<";
    ofLogVerbose("ofxOAuth::post") << "http    HEADER >" << http_hdr << "<";
    
    char* p_reply = ofx_oauth_curl_post(req_url.c_str(),   // the base url to get
                                        post_params,       // the query string to send
                                        http_hdr.c_str()); // Authorization header is included here
    
    if(0 != post_params)
    {
        free(post_params);
    }
    
    if(0 != p_reply)
    {
        reply = p_reply;
        free(p_reply);
    }
    
    if (reply.empty())
    {
        ofLogVerbose("ofxOAuth::post") << "HTTP post request failed.";
    }
    else
    {
        ofLogVerbose("ofxOAuth::post") << "HTTP-Reply: " << reply;
        result = reply;
    }
    
    return result;
}


std::string ofxOAuth::postfile_multipartdata(const std::string& uri, const std::string& query, const std::string& filefieldname, const std::string& filepath)
{
 
    std::string result = "";
    
    if(apiURL.empty())
    {
        ofLogError("ofxOAuth::postfile_multipartdata") << "No api URL specified.";
        return result;
    }
    
    if(consumerKey.empty())
    {
        ofLogError("ofxOAuth::postfile_multipartdata") << "No consumer key specified.";
        return result;
    }
    
    if(consumerSecret.empty())
    {
        ofLogError("ofxOAuth::postfile_multipartdata") << "No consumer secret specified.";
        return result;
    }
    
    if(accessToken.empty())
    {
        ofLogError("ofxOAuth::postfile_multipartdata") << "No access token specified.";
        return result;
    }
    
    if(accessTokenSecret.empty())
    {
        ofLogError("ofxOAuth::postfile_multipartdata") << "No access token secret specified.";
        return result;
    }
    
    std::string req_url;
    std::string req_hdr;
    std::string http_hdr;
    
    std::string reply;
    
    // oauth_sign_url2 (see oauth.h) in steps
    int  argc   = 0;
    char **argv = 0;
    
    // break apart the url parameters to they can be signed below
    // if desired we can also pass in additional patermeters (like oath* params)
    // here.  For instance, if ?oauth_callback=XXX is defined in this url,
    // it will be parsed and used in the Authorization header.
    
    std::string url = apiURL + uri;
    
    argc = oauth_split_url_parameters(url.c_str(), &argv);
    
    // sign the array.
    oauth_sign_array2_process(&argc,
                              &argv,
                              0, //< postargs (unused)
                              _getOAuthMethod(), // hash type, OA_HMAC, OA_RSA, OA_PLAINTEXT
                              "POST", //< HTTP method (defaults to "GET")
                              consumerKey.c_str(), //< consumer key - posted plain text
                              consumerSecret.c_str(), //< consumer secret - used as 1st part of secret-key
                              accessToken.c_str(),  //< token key - posted plain text in URL
                              accessTokenSecret.c_str()); //< token secret - used as 2st part of secret-key
    
    ofLogVerbose("ofxOAuth::postfile_multipartdata") << "-------------------";
    ofLogVerbose("ofxOAuth::postfile_multipartdata") << "consumerKey          >" << consumerKey << "<";
    ofLogVerbose("ofxOAuth::postfile_multipartdata") << "consumerSecret       >" << consumerSecret << "<";
    ofLogVerbose("ofxOAuth::postfile_multipartdata") << "requestToken         >" << requestToken << "<";
    ofLogVerbose("ofxOAuth::postfile_multipartdata") << "requestTokenVerifier >" << requestTokenVerifier << "<";
    ofLogVerbose("ofxOAuth::postfile_multipartdata") << "requestTokenSecret   >" << requestTokenSecret << "<";
    ofLogVerbose("ofxOAuth::postfile_multipartdata") << "accessToken          >" << accessToken << "<";
    ofLogVerbose("ofxOAuth::postfile_multipartdata") << "accessTokenSecret    >" << accessTokenSecret << "<";
    ofLogVerbose("ofxOAuth::postfile_multipartdata") << "-------------------";
    
    req_url =  apiURL + uri;
    
    // collect any of the oauth parameters for inclusion in the HTTP Authorization header.
    char* p_req_hdr = oauth_serialize_url_sep(argc, 1, argv, const_cast<char *>(", "), 2); // const_cast<char *>() is to avoid Deprecated
    
    if(0 != p_req_hdr)
    {
        req_hdr = p_req_hdr;
        free(p_req_hdr);
    }
    
    // look at url parameters to be signed if you want.
    if(ofGetLogLevel() <= OF_LOG_VERBOSE)
        for (int i=0;i<argc; i++) ofLogVerbose("ofxOAuth::postfile_multipartdata") << " : " << i << ":" << argv[i];
    
    // free our parameter arrays that were allocated during parsing above
    oauth_free_array(&argc, &argv);
    //oauth_free_array(&argcp, &argvp);
    
    // construct the Authorization header.  Include realm information if available.
    if(!realm.empty())
    {
        // Note that (optional) 'realm' is not to be
        // included in the oauth signed parameters and thus only added here.
        // see 9.1.1 in http://oauth.net/core/1.0/#anchor14
        http_hdr = "Authorization: OAuth realm=\"" + realm + "\", " + req_hdr;
    }
    else
    {
        http_hdr = "Authorization: OAuth " + req_hdr;
    }
    
    ofLogVerbose("ofxOAuth::postfile_multipartdata") << "request URL    >" << req_url << "<";
    ofLogVerbose("ofxOAuth::postfile_multipartdata") << "request HEADER >" << req_hdr << "<";
    ofLogVerbose("ofxOAuth::postfile_multipartdata") << "http    HEADER >" << http_hdr << "<";
    
    char* p_reply = ofx_oauth_curl_post_file_multipartformdata(
                                        req_url.c_str(),   // the base url to get
                                        query,       // string containing additional params to send (separated by &)
                                        filefieldname.c_str(), // the name of the field that will hold filedata on the form
                                        filepath.c_str(), // Absolute path of the file you want to send
                                        0,              // length of the file in bytes. set to '0' for autodetection
                                        http_hdr.c_str()); // Authorization header is included here
    
    if(0 != p_reply)
    {
        reply = p_reply;
        free(p_reply);
    }
     
    if (reply.empty())
    {
        ofLogVerbose("ofxOAuth::postfile_multipartdata") << "HTTP post request failed.";
    }
    else
    {
        ofLogVerbose("ofxOAuth::postfile_multipartdata") << "HTTP-Reply: " << reply;
        result = reply;
    }
    
    return result;
    
}


std::map<std::string, std::string> ofxOAuth::obtainRequestToken()
{
    std::map<std::string, std::string> returnParams;

    if(requestTokenURL.empty())
    {
        ofLogError("ofxOAuth::obtainRequestToken") << "No request token URL specified.";
        return returnParams;
    }
    
    if(consumerKey.empty())
    {
        ofLogError("ofxOAuth::obtainRequestToken") << "No consumer key specified.";
        return returnParams;
    }

    if(consumerSecret.empty())
    {
        ofLogError("ofxOAuth::obtainRequestToken") << "No consumer secret specified.";
        return returnParams;
    }

    std::string req_url;
    std::string req_hdr;
    std::string http_hdr;

    std::string reply;

    // oauth_sign_url2 (see oauth.h) in steps
    int  argc   = 0;
    char **argv = 0;
    
    // break apart the url parameters to they can be signed below
    // if desired we can also pass in additional patermeters (like oath* params)
    // here.  For instance, if ?oauth_callback=XXX is defined in this url,
    // it will be parsed and used in the Authorization header.
    argc = oauth_split_url_parameters(requestTokenURL.c_str(), &argv);
    
    // add the authorization callback url info if available
    if(!getVerifierCallbackURL().empty())
    {
        std::string callbackParam = "oauth_callback=" + getVerifierCallbackURL();
        oauth_add_param_to_array(&argc, &argv, callbackParam.c_str());
    }

    // NOTE BELOW:
    /*
     
    FOR GOOGLE:
    Authorization header of a GET or POST request. Use "Authorization: OAuth". All parameters listed above can go in the header, except for scope and xoauth_displayname, which must go either in the body or in the URL as a query parameter. The example below puts them in the body of the request.
    
     https://developers.google.com/accounts/docs/OAuth_ref#RequestToken
     */
    
    if(!getApplicationDisplayName().empty())
    {
        std::string displayNameParam = "xoauth_displayname=" + getApplicationDisplayName();
        oauth_add_param_to_array(&argc, &argv, displayNameParam.c_str());
    }
    
    if(!getApplicationScope().empty())
    {
        // TODO: this will not be integrated correctly by lib oauth
        // b/c it does not have a oauth / xoauth prefix
        // XXXXXXXXXX
        std::string scopeParam = "scope=" + getApplicationScope();
        oauth_add_param_to_array(&argc, &argv, scopeParam.c_str());
    }
    
    
    // NOTE: if desired, normal oatuh parameters, such as oauth_nonce could be overriden here
    // rathern than having them auto-calculated using the oauth_sign_array2_process method
    //oauth_add_param_to_array(&argc, &argv, "oauth_nonce=xxxxxxxpiOuDKDAmwHKZXXhGelPc4cJq");

    // sign the array.
    oauth_sign_array2_process(&argc, 
                              &argv,
                              0, //< postargs (unused)
                              _getOAuthMethod(), // hash type, OA_HMAC, OA_RSA, OA_PLAINTEXT
                              _getHttpMethod().c_str(), //< HTTP method (defaults to "GET")
                              consumerKey.c_str(), //< consumer key - posted plain text
                              consumerSecret.c_str(), //< consumer secret - used as 1st part of secret-key
                              0,  //< token key - posted plain text in URL
                              0); //< token secret - used as 2st part of secret-key
    
    ofLogVerbose("ofxOAuth::obtainRequestToken") << "-------------------";
    ofLogVerbose("ofxOAuth::obtainRequestToken") << "consumerKey          >" << consumerKey << "<";
    ofLogVerbose("ofxOAuth::obtainRequestToken") << "consumerSecret       >" << consumerSecret << "<";
    ofLogVerbose("ofxOAuth::obtainRequestToken") << "requestToken         >" << requestToken << "<";
    ofLogVerbose("ofxOAuth::obtainRequestToken") << "requestTokenVerifier >" << requestTokenVerifier << "<";
    ofLogVerbose("ofxOAuth::obtainRequestToken") << "requestTokenSecret   >" << requestTokenSecret << "<";
    ofLogVerbose("ofxOAuth::obtainRequestToken") << "accessToken          >" << accessToken << "<";
    ofLogVerbose("ofxOAuth::obtainRequestToken") << "accessTokenSecret    >" << accessTokenSecret << "<";
    ofLogVerbose("ofxOAuth::obtainRequestToken") << "-------------------";

    // collect any parameters in our list that need to be placed in the request URI
    char* p_req_url = oauth_serialize_url_sep(argc, 0, argv, const_cast<char *>("&"), 1);

    if(0 != p_req_url)
    {
        req_url = p_req_url;
        free(p_req_url);
    }

    // collect any of the oauth parameters for inclusion in the HTTP Authorization header.
    char* p_req_hdr = oauth_serialize_url_sep(argc, 1, argv, const_cast<char *>(", "), 6); // const_cast<char *>() is to avoid Deprecated

    if(0 != p_req_hdr)
    {
        req_hdr = p_req_hdr;
        free(p_req_hdr);
    }

    // look at url parameters to be signed if you want.
    if(ofGetLogLevel() <= OF_LOG_VERBOSE)
        for (int i=0;i<argc; i++) ofLogVerbose("ofxOAuth::obtainRequestToken") << i << " >" << argv[i] << "<";

    // free our parameter arrays that were allocated during parsing above    
    oauth_free_array(&argc, &argv);
    
    // construct the Authorization header.  Include realm information if available.
    if(!realm.empty())
    {
        // Note that (optional) 'realm' is not to be 
        // included in the oauth signed parameters and thus only added here.
        // see 9.1.1 in http://oauth.net/core/1.0/#anchor14
        http_hdr = "Authorization: OAuth realm=\"" + realm + "\", " + req_hdr; 
    }
    else
    {
        http_hdr = "Authorization: OAuth " + req_hdr;
    }

    ofLogVerbose("ofxOAuth::obtainRequestToken") << "Request URL    = " << req_url;
    ofLogVerbose("ofxOAuth::obtainRequestToken") << "Request HEADER = " << req_hdr;
    ofLogVerbose("ofxOAuth::obtainRequestToken") << "http    HEADER = " << http_hdr;
    




    char* p_reply = ofx_oauth_http_get2(req_url.c_str(),   // the base url to get
                                    0,              // the query string to send
                                    http_hdr.c_str(),
                                        SSLCACertificateFile.c_str()); // Authorization header is included here

    if(0 != p_reply)
    {
        reply = p_reply;
        free(p_reply);
    }

    if (reply.empty())
    {
        ofLogVerbose("ofxOAuth::obtainRequestToken") << "HTTP request for an oauth request-token failed.";
    }
    else
    {
        ofLogVerbose("ofxOAuth::obtainRequestToken") << "HTTP-Reply: " << reply;

        // could use oauth_split_url_parameters here.
        std::vector<std::string> params = ofSplitString(reply, "&", true);

        for(int i = 0; i < params.size(); i++)
        {
            std::vector<std::string> tokens = ofSplitString(params[i], "=");
            if(tokens.size() == 2)
            {
                returnParams[tokens[0]] = tokens[1];
                
                if(Poco::icompare(tokens[0],"oauth_token") == 0)
                {
                    requestToken = tokens[1];
                }
                else if(Poco::icompare(tokens[0],"oauth_token_secret") == 0)
                {
                    requestTokenSecret = tokens[1];
                }
                else if(Poco::icompare(tokens[0],"oauth_callback_confirmed") == 0)
                {
                    callbackConfirmed = ofToBool(tokens[1]);
                }
                else if(Poco::icompare(tokens[0],"oauth_problem") == 0)
                {
                    ofLogError("ofxOAuth::obtainRequestToken") <<  "Got oauth problem: " << tokens[1];
                }
                else
                {
                    ofLogNotice("ofxOAuth::obtainRequestToken") << "Got an unknown parameter: " << tokens[0] << "=" + tokens[1];
                }
            }
            else
            {
                ofLogWarning("ofxOAuth::obtainRequestToken") <<  "Return parameter did not have 2 values: " << params[i] << " - skipping.";
            }
        }
    }
    
    if(requestTokenSecret.empty())
    {
        ofLogWarning("ofxOAuth::obtainRequestToken") << "Request token secret not returned.";
        accessFailed = true;
    }

    if(requestToken.empty())
    {
        ofLogWarning("ofxOAuth::obtainRequestToken") << "Request token not returned.";
        accessFailed = true;
    }

    
    return returnParams;
}


std::map<std::string,std::string> ofxOAuth::obtainAccessToken()
{
    std::map<std::string,std::string> returnParams;
    
    if(accessTokenURL.empty())
    {
        ofLogError("ofxOAuth::obtainAccessToken") << "No access token URL specified.";
        return returnParams;
    }
    
    if(consumerKey.empty())
    {
        ofLogError("ofxOAuth::obtainAccessToken") << "No consumer key specified.";
        return returnParams;
    }
    
    if(consumerSecret.empty())
    {
        ofLogError("ofxOAuth::obtainAccessToken") << "No consumer secret specified.";
        return returnParams;
    }
    
    if(requestToken.empty())
    {
        ofLogError("ofxOAuth::obtainAccessToken") << "No request token specified.";
        return returnParams;
    }
    
    if(requestTokenSecret.empty())
    {
        ofLogError("ofxOAuth::obtainAccessToken") << "No request token secret specified.";
        return returnParams;
    }
    
    if(requestTokenVerifier.empty())
    {
        ofLogError("ofxOAuth::obtainAccessToken") << "No request token verifier specified.";
        return returnParams;
    }
    
    std::string req_url;
    std::string req_hdr;
    std::string http_hdr;
    
    std::string reply;
    
    // oauth_sign_url2 (see oauth.h) in steps
    int  argc   = 0;
    char **argv = 0;
    
    // break apart the url parameters to they can be signed below
    // if desired we can also pass in additional patermeters (like oath* params)
    // here.  For instance, if ?oauth_callback=XXX is defined in this url,
    // it will be parsed and used in the Authorization header.
    argc = oauth_split_url_parameters(getAccessTokenURL().c_str(), &argv);
    
    // add the verifier param
    std::string verifierParam = "oauth_verifier=" + requestTokenVerifier;
    oauth_add_param_to_array(&argc, &argv, verifierParam.c_str());

    // NOTE: if desired, normal oauth parameters, such as oauth_nonce could be overriden here
    // rathern than having them auto-calculated using the oauth_sign_array2_process method
    //oauth_add_param_to_array(&argc, &argv, "oauth_nonce=xxxxxxxpiOuDKDAmwHKZXXhGelPc4cJq");
    
    // sign the array.
    oauth_sign_array2_process(&argc, 
                              &argv,
                              0, //< postargs (unused)
                              _getOAuthMethod(), // hash type, OA_HMAC, OA_RSA, OA_PLAINTEXT
                              _getHttpMethod().c_str(), //< HTTP method (defaults to "GET")
                              consumerKey.c_str(), //< consumer key - posted plain text
                              consumerSecret.c_str(), //< consumer secret - used as 1st part of secret-key
                              requestToken.c_str(),  //< token key - posted plain text in URL
                              requestTokenSecret.c_str()); //< token secret - used as 2st part of secret-key

    ofLogVerbose("ofxOAuth::obtainAccessToken") << "-------------------";
    ofLogVerbose("ofxOAuth::obtainAccessToken") << "consumerKey          >" << consumerKey << "<";
    ofLogVerbose("ofxOAuth::obtainAccessToken") << "consumerSecret       >" << consumerSecret << "<";
    ofLogVerbose("ofxOAuth::obtainAccessToken") << "requestToken         >" << requestToken << "<";
    ofLogVerbose("ofxOAuth::obtainAccessToken") << "requestTokenVerifier >" << requestTokenVerifier << "<";
    ofLogVerbose("ofxOAuth::obtainAccessToken") << "requestTokenSecret   >" << requestTokenSecret << "<";
    ofLogVerbose("ofxOAuth::obtainAccessToken") << "accessToken          >" << accessToken << "<";
    ofLogVerbose("ofxOAuth::obtainAccessToken") << "accessTokenSecret    >" << accessTokenSecret << "<";
    ofLogVerbose("ofxOAuth::obtainAccessToken") << "-------------------";
    
    // collect any parameters in our list that need to be placed in the request URI
    char* p_req_url = oauth_serialize_url_sep(argc, 0, argv, const_cast<char *>("&"), 1);

    if(0 != p_req_url)
    {
        req_url = p_req_url;
        free(p_req_url);
    }
    
    // collect any of the oauth parameters for inclusion in the HTTP Authorization header.
    char* p_req_hdr = oauth_serialize_url_sep(argc, 1, argv, const_cast<char *>(", "), 6); // const_cast<char *>() is to avoid Deprecated

    if(0 != p_req_hdr)
    {
        req_hdr = p_req_hdr;
        free(p_req_hdr);
    }

    // look at url parameters to be signed if you want.
    if(ofGetLogLevel() <= OF_LOG_VERBOSE)
    {
        for(int i=0; i < argc; i++)
        {
            ofLogVerbose("ofxOAuth::obtainAccessToken") << i << " >" << argv[i] << "<";
        }
    }
    
    // free our parameter arrays that were allocated during parsing above    
    oauth_free_array(&argc, &argv);
    
    // construct the Authorization header.  Include realm information if available.
    if(!realm.empty())
    {
        // Note that (optional) 'realm' is not to be 
        // included in the oauth signed parameters and thus only added here.
        // see 9.1.1 in http://oauth.net/core/1.0/#anchor14
        http_hdr = "Authorization: OAuth realm=\"" + realm + "\", " + req_hdr; 
    }
    else
    {
        http_hdr = "Authorization: OAuth " + req_hdr; 
    }
    
    ofLogVerbose("ofxOAuth::obtainAccessToken") << "request URL    >" << req_url << "<";
    ofLogVerbose("ofxOAuth::obtainAccessToken") << "request HEADER >" << req_hdr << "<";
    ofLogVerbose("ofxOAuth::obtainAccessToken") << "http    HEADER >" << http_hdr << "<";
    
    char* p_reply = ofx_oauth_http_get2(req_url.c_str(),   // the base url to get
                                     0,              // the query string to send
                                     http_hdr.c_str(),
                                        SSLCACertificateFile.c_str()); // Authorization header is included here
    
    if(0 != p_reply)
    {
        reply = p_reply;
        free(p_reply);
    }

    if (reply.empty())
    {
        ofLogVerbose("ofxOAuth::obtainAccessToken") << "HTTP request for an oauth request-token failed.";
    }
    else
    {
        ofLogVerbose("ofxOAuth::obtainAccessToken") << "HTTP-Reply >" << reply << "<";
        
        // could use oauth_split_url_parameters here.
        std::vector<std::string> params = ofSplitString(reply, "&", true);
        
        for(int i = 0; i < params.size(); i++)
        {
            std::vector<std::string> tokens = ofSplitString(params[i], "=");
            if(tokens.size() == 2)
            {
                returnParams[tokens[0]] = tokens[1];
                
                if(Poco::icompare(tokens[0],"oauth_token") == 0)
                {
                    accessToken = tokens[1];
                }
                else if(Poco::icompare(tokens[0],"oauth_token_secret") == 0)
                {
                    accessTokenSecret = tokens[1];
                }
                else if(Poco::icompare(tokens[0],"oauth_problem") == 0)
                {
                    ofLogError("ofxOAuth::obtainAccessToken") << "Got oauth problem: " << tokens[1];
                }
                else
                {
                    ofLogNotice("ofxOAuth::obtainAccessToken") << "got an unknown parameter: " << tokens[0] << "=" << tokens[1];
                    customInfo[tokens[0]] = tokens[1];
                }
            }
            else
            {
                ofLogWarning("ofxOAuth::obtainAccessToken") << "Return parameter did not have 2 values: "  << params[i] << " - skipping.";
            }
        }
    }
    
    if(accessTokenSecret.empty())
    {
        ofLogWarning("ofxOAuth::obtainAccessToken") << "Access token secret not returned.";
        accessFailed = true;
    }
    
    if(accessToken.empty())
    {
        ofLogWarning("ofxOAuth::obtainAccessToken") << "Access token not returned.";
        accessFailed = true;
    }
    
    // save it to an xml file!
    saveCredentials();
    
    return returnParams;
}


std::string ofxOAuth::requestUserVerification(bool launchBrowser)
{
    return requestUserVerification("",launchBrowser);
}

//--------------------------------------------------------------
std::string ofxOAuth::requestUserVerification(std::string additionalAuthParams,
                                              bool launchBrowser)
{
    
    std::string url = getAuthorizationURL();
    
    if(url.empty())
    {
        ofLogError("ofxOAuth::requestUserVerification") << "Authorization URL is not set.";
        return "";
    }
    
    url += "oauth_token=";
    url += getRequestToken();
    url += additionalAuthParams;

    if(launchBrowser) ofLaunchBrowser(url);

    return url;
}


std::string ofxOAuth::getApiURL()
{
    return apiURL;
}


void ofxOAuth::setApiURL(const std::string &v, bool autoSetEndpoints)
{
    apiURL = v; 
    if(autoSetEndpoints)
    {
        setRequestTokenURL(apiURL + "/oauth/request_token");
        setAccessTokenURL(apiURL + "/oauth/access_token");
        setAuthorizationURL(apiURL + "/oauth/authorize");
    }
}


std::string ofxOAuth::getRequestTokenURL()
{
    return requestTokenURL;
}


void ofxOAuth::setRequestTokenURL(const std::string& v)
{
    requestTokenURL = appendQuestionMark(v);
}


std::string ofxOAuth::getAccessTokenURL()
{
    return accessTokenURL;
}


void ofxOAuth::setAccessTokenURL(const std::string& v)
{
    accessTokenURL = appendQuestionMark(v);
}


std::string ofxOAuth::getAuthorizationURL()
{
    return authorizationURL;
}


void ofxOAuth::setAuthorizationURL(const std::string& v)
{
    authorizationURL = appendQuestionMark(v);
}


std::string ofxOAuth::getVerifierCallbackURL()
{
    return verifierCallbackURL;
}


void ofxOAuth::setVerifierCallbackURL(const std::string& v)
{
    verifierCallbackURL = v;
}


void ofxOAuth::setApplicationDisplayName(const std::string& v)
{
    applicationDisplayName = v;
}


std::string ofxOAuth::getApplicationDisplayName()
{
    return applicationDisplayName;
}


void ofxOAuth::setApplicationScope(const std::string& v)
{
    // google specific
    applicationScope = v;
}


std::string ofxOAuth::getApplicationScope()
{
    return applicationScope;
}


bool ofxOAuth::isVerifierCallbackServerEnabled()
{
    return enableVerifierCallbackServer;
}


void ofxOAuth::setVerifierCallbackServerDocRoot(const std::string& v)
{
    verifierCallbackServerDocRoot = v;
}


std::string ofxOAuth::getVerifierCallbackServerDocRoot()
{
    return verifierCallbackServerDocRoot;
}


bool ofxOAuth::isVerifierCallbackPortSet() const
{
    return vertifierCallbackServerPort > 0;
}


int ofxOAuth::getVerifierCallbackServerPort() const
{
    return vertifierCallbackServerPort;
}


void ofxOAuth::setVerifierCallbackServerPort(int portNumber)
{
    vertifierCallbackServerPort = portNumber;
}


void ofxOAuth::setEnableVerifierCallbackServer(bool v)
{
    enableVerifierCallbackServer = v;
}


std::string ofxOAuth::getRequestToken()
{
    return requestToken;
}


void ofxOAuth::setRequestToken(const std::string& v)
{
    requestToken = v;
}


std::string ofxOAuth::getRequestTokenSecret()
{
    return requestTokenSecret;
}


void ofxOAuth::setRequestTokenSecret(const std::string& v)
{
    requestTokenSecret = v;
}


std::string ofxOAuth::getRequestTokenVerifier()
{
    return requestTokenVerifier;
}


void ofxOAuth::setRequestTokenVerifier(const std::string& _requestToken,
                                       const std::string& _requestTokenVerifier)
{
    if(_requestToken == getRequestToken())
    {
        setRequestTokenVerifier(_requestTokenVerifier);
    }
    else
    {
        ofLogError("ofxOAuth::getRequestToken") << "The request token didn't match the request token on record.";
    }
}


void ofxOAuth::setRequestTokenVerifier(const std::string& v)
{
    requestTokenVerifier = v;
}


std::string ofxOAuth::getAccessToken()
{
    return accessToken;
}


void ofxOAuth::setAccessToken(const std::string& v)
{
    accessToken = v;
}


std::string ofxOAuth::getAccessTokenSecret()
{
    return accessTokenSecret;
}


void ofxOAuth::setAccessTokenSecret(const std::string& v)
{
    accessTokenSecret = v;
}


std::string ofxOAuth::getEncodedUserId()
{
    return encodedUserId;
}


void ofxOAuth::setEncodedUserId(const std::string& v)
{
    encodedUserId = v;
}


std::string ofxOAuth::getUserId()
{
    return userId;
}


void ofxOAuth::setUserId(const std::string& v)
{
    userId = v;
}


std::string ofxOAuth::getEncodedUserPassword()
{
    return encodedUserPassword;
}


void ofxOAuth::setEncodedUserPassword(const std::string& v)
{
    encodedUserPassword = v;
}


std::string ofxOAuth::getUserPassword()
{
    return userPassword;
}


void ofxOAuth::setUserPassword(const std::string& v)
{
    userPassword = v;
}


std::string ofxOAuth::getConsumerKey() const
{
    return consumerKey;
}


void ofxOAuth::setConsumerKey(const std::string& v)
{
    consumerKey = v;
}

std::string ofxOAuth::getConsumerSecret() const
{
    return consumerSecret;
}


void ofxOAuth::setConsumerSecret(const std::string& v)
{
    consumerSecret = v;
}


void ofxOAuth::setApiName(const std::string& v)
{
    apiName = v;
}


std::string ofxOAuth::getApiName() const
{
    return apiName;
}

void ofxOAuth::receivedVerifierCallbackRequest(const Poco::Net::HTTPServerRequest& request)
{
    ofLogVerbose("ofxOAuth::receivedVerifierCallbackRequest") << "Not implemented.";
    // does nothing with this, but subclasses might.
}


void ofxOAuth::receivedVerifierCallbackHeaders(const Poco::Net::NameValueCollection& headers)
{
    ofLogVerbose("ofxOAuth::receivedVerifierCallbackHeaders") << "Not implemented.";
    // for(NameValueCollection::ConstIterator iter = headers.begin(); iter != headers.end(); iter++) {
    //    ofLogVerbose("ofxOAuth::receivedVerifierCallbackHeaders") << (*iter).first << "=" << (*iter).second;
    //}
    // does nothing with this, but subclasses might.
}


void ofxOAuth::receivedVerifierCallbackCookies(const Poco::Net::NameValueCollection& cookies)
{
    for(Poco::Net::NameValueCollection::ConstIterator iter = cookies.begin();
        iter != cookies.end();
        iter++)
    {
        ofLogVerbose("ofxOAuth::receivedVerifierCallbackCookies") << (*iter).first << "=" << (*iter).second;
    }
    // does nothing with this, but subclasses might.
}


void ofxOAuth::receivedVerifierCallbackGetParams(const Poco::Net::NameValueCollection& getParams)
{
    for(Poco::Net::NameValueCollection::ConstIterator iter = getParams.begin();
        iter != getParams.end();
        iter++) {
        ofLogVerbose("ofxOAuth::receivedVerifierCallbackGetParams") << (*iter).first << "=" << (*iter).second;
    }

    // we normally extract these params
    if(getParams.has("oauth_token") && getParams.has("oauth_verifier"))
    {
        setRequestTokenVerifier(getParams.get("oauth_token"), getParams.get("oauth_verifier"));
    }
    
    // subclasses might also want to extract other get parameters.    
}


void ofxOAuth::receivedVerifierCallbackPostParams(const Poco::Net::NameValueCollection& postParams)
{
    // come soon c++11!
    for(Poco::Net::NameValueCollection::ConstIterator iter = postParams.begin();
        iter != postParams.end();
        iter++)
    {
        ofLogVerbose("ofxOAuth::receivedVerifierCallbackPostParams") << (*iter).first << "=" << (*iter).second;
    }
    
    // does nothing with this, but subclasses might.
}


std::string ofxOAuth::getRealm() const
{
    return realm;
}


void ofxOAuth::setRealm(const std::string& v)
{
    realm = v;
}


bool ofxOAuth::isAuthorized()
{
    return !accessToken.empty() && !accessTokenSecret.empty();
}


void ofxOAuth::saveCredentials()
{
    ofxXmlSettings XML;

    XML.getValue("oauth:api_url", apiURL);
    XML.getValue("oauth:api_request_token_url", requestTokenURL);
    XML.getValue("oauth:api_access_token_url", accessTokenURL);
    XML.getValue("oauth:api_authorization_url", authorizationURL);
    XML.getValue("oauth:verifier_callback_url", verifierCallbackURL);

    XML.getValue("oauth:api_name", apiName);

    XML.setValue("oauth:consumer_key", consumerKey);
    XML.setValue("oauth:consumer_secret", consumerSecret);

    XML.setValue("oauth:access_token", accessToken);

    XML.setValue("oauth:access_secret",accessTokenSecret);

    // set additional info

    if(!XML.saveFile(credentialsPathname))
    {
        ofLogError("ofxOAuth::saveCredentials") << "Failed to save : " << credentialsPathname;
    }

}


void ofxOAuth::loadCredentials()
{
    ofxXmlSettings XML;
    
    if(XML.loadFile(credentialsPathname))
    {
//        <oauth api="GENERIC">
//          <api>
//              <name></name>
//              <request_token_url></<request_token_url>
//              <access_token_url></<access_token_url>
//              <authorize_url></<authorize_url>
//          </api>
//          <consumer_token></consumer_token>
//          <consumer_secret></consumer_secret>
//          <access_token></access_token>
//          <access_secret></access_secret>
//          <custom>
//              <user_id></user_id>
//              <user_id_encoded></user_id_encoded>
//              <user_password></user_password>
//              <user_password_encoded></user_password_encoded>
//          </custom>
//        </oauth>

        std::string _consumerKey = XML.getValue("oauth:consumer_key", "");
        std::string _consumerSecret = XML.getValue("oauth:consumer_secret", "");

        std::string _accessToken = XML.getValue("oauth:access_token", "");
        std::string _accessSecret = XML.getValue("oauth:access_secret", "");

        std::string _apiName = XML.getValue("oauth:api::name", "");

        std::string _apiRequestTokenUrl = XML.getValue("oauth:api::request_token_url", "");
        std::string _apiAccessTokenUrl = XML.getValue("oauth:api::access_token_url", "");
        std::string _apiAuthorizeUrl = XML.getValue("oauth:api::authorize_url", "");



        if(!consumerKey.empty() &&
           (XML.getValue("oauth:consumer_key","") != consumerKey ||
            XML.getValue("oauth:consumer_secret","") != consumerSecret))
        {
            ofLogError("ofxOAuth::loadCredentials") << "Found a credential file, but did not match the consumer secret / key provided.  Please delete your credentials file: " + ofToDataPath(credentialsPathname) + " and try again.";
            return;
        }


        if(XML.getValue("oauth:access_token", "").empty() ||
           XML.getValue("oauth:access_secret","").empty())
        {
            ofLogError("ofxOAuth::loadCredentials") << "Found a credential file, but access token / secret were empty.  Please delete your credentials file: " + ofToDataPath(credentialsPathname) + " and try again.";
            return;
        }

        std::string _apiURL = XML.getValue("oauth:api_url", "");

        if (!_apiURL.empty())
        {
            setApiURL(_apiURL);
        }

//        XML.getValue("oauth:api_url", apiURL);
//        XML.getValue("oauth:api_request_token_url", requestTokenURL);
//        XML.getValue("oauth:api_access_token_url", accessTokenURL);
//        XML.getValue("oauth:api_authorization_url", authorizationURL);
//        XML.getValue("oauth:verifier_callback_url", verifierCallbackURL);

        apiName             = XML.getValue("oauth:api_name", "");

        accessToken         = XML.getValue("oauth:access_token", "");
        accessTokenSecret   = XML.getValue("oauth:access_secret","");

        screenName          = XML.getValue("oauth:screen_name","");
        
        userId              = XML.getValue("oauth:user_id", "");
        encodedUserId       = XML.getValue("oauth:user_id_encoded","");

        userPassword        = XML.getValue("oauth:user_password", "");
        encodedUserPassword = XML.getValue("oauth:user_password_encoded","");        
    }
    else
    {
        ofLogNotice("ofxOAuth::loadCredentials") << "Unable to locate credentials file: " << ofToDataPath(credentialsPathname);
    }
    
}


void ofxOAuth::setCredentialsPathname(const std::string& credentials)
{
    credentialsPathname = credentials;
}


std::string ofxOAuth::getCredentialsPathname()
{
    return credentialsPathname;
}


void ofxOAuth::resetErrors()
{
    accessFailed = false;
    accessFailedReported = false;
}


ofxOAuth::AuthMethod ofxOAuth::getOAuthMethod()
{
    return oauthMethod;
}


void ofxOAuth::setOAuthMethod(AuthMethod _oauthMethod)
{
    oauthMethod = _oauthMethod;
}


void ofxOAuth::setSSLCACertificateFile(const std::string& pathname)
{
    SSLCACertificateFile = ofToDataPath(pathname,true);
    // setenv("CURLOPT_CAINFO", ofToDataPath(SSLCACertificateFile,true).c_str(), true);
    ofLogVerbose("ofxOAuth::setSSLCACertificateFile") << "Set CACERT to : " << SSLCACertificateFile;
}


OAuthMethod ofxOAuth::_getOAuthMethod()
{
    switch (oauthMethod)
    {
        case OFX_OA_HMAC:
            return OA_HMAC;
        case OFX_OA_RSA:
            return OA_RSA;
        case OFX_OA_PLAINTEXT:
            return OA_PLAINTEXT;
        default:
            ofLogError("ofxOAuth::_getOAuthMethod") << "Unknown OAuthMethod, defaulting to OA_HMAC. oauthMethod=" << oauthMethod;
            return OA_HMAC;
    }
}


std::string ofxOAuth::_getHttpMethod()
{
    switch (httpMethod)
    {
        case OFX_HTTP_GET:
            return "GET";
        case OFX_HTTP_POST:
            return "POST";
        default:
            ofLogError("ofxOAuth::_getHttpMethod") << "Unknown HttpMethod, defaulting to GET. httpMethod=" << httpMethod;
            return "GET";
    }
}


std::string ofxOAuth::appendQuestionMark(const std::string& url) const
{
    std::string u = url;
    if(!u.empty() && u.substr(u.size()-1,u.size()-1) != "?") u += "?"; // need that
    return u;
}
