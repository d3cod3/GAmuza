/**
 *  ofxCrypto.h
 *
 * Created by Jamie Kosoy, http://jkosoy.com
 *
 *
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * ----------------------
 *
 *  ofxCrypto wraps Pocos' built in encryption engines to provide base64, md5 and sha1 encryption easily in oF.
 *  Base64 Encoding and Decoding can also be done with ofBuffers, for when binary files need to be encoded as strings.
 *  Usage::
 *      ofxCrypto::md5("hello world");
 *      ofxCrypto::sha1("hello world");
 *      ofxCrypto::base64_encode("hello world");
 *      ofxCrypto::base64_decode("aGVsbG8gd29ybGQ="); // hello world.
 *
 */


#pragma once

#include "ofMain.h"

#include "Poco/MD5Engine.h"
#include "Poco/SHA1Engine.h"
#include "Poco/DigestStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Base64Decoder.h"
#include "Poco/Base64Encoder.h"

using Poco::DigestEngine;
using Poco::MD5Engine;
using Poco::SHA1Engine;
using Poco::Base64Encoder;
using Poco::Base64Decoder;
using Poco::DigestOutputStream;
using Poco::StreamCopier;

class ofxCrypto {
    public:
        ofxCrypto();
        ~ofxCrypto();
    
        string md5(string source);
        string sha1(string source);
        string base64_encode(string source);
        string base64_decode(string source);

        string base64_encode(ofBuffer &buffer);
        ofBuffer base64_decode_to_buffer(string source);
};
