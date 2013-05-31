/**
 *  ofxCrypto.cpp
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

#include "ofxCrypto.h"

ofxCrypto::ofxCrypto() {
   
}

ofxCrypto::~ofxCrypto() {
    
}

string ofxCrypto::md5(string source) {
    MD5Engine engine;

    engine.update(source);
    return DigestEngine::digestToHex(engine.digest());
}

string ofxCrypto::sha1(string source) {
    SHA1Engine engine;

    engine.update(source);
    return DigestEngine::digestToHex(engine.digest());
}

string ofxCrypto::base64_encode(string source) {
    ostringstream ostr;
    Base64Encoder encoder(ostr);
    encoder << source;
    encoder.close();
    
    return ostr.str();
}

string ofxCrypto::base64_decode(string source) {
    ostringstream ostr;
    istringstream istr(source);

    Base64Decoder decoder(istr);
    StreamCopier::copyStream(decoder, ostr);

    return ostr.str();
}

string ofxCrypto::base64_encode(ofBuffer &buffer) {
    long max = buffer.size();
    char *buf = buffer.getBinaryBuffer();

    string str = string(buf,max);

    return base64_encode(str);
}

// jamie :: this gist helped a bunch :: https://gist.github.com/satoruhiga/1687325
ofBuffer ofxCrypto::base64_decode_to_buffer(string source) {
    stringstream ss;
	ss << source;
	Poco::Base64Decoder decoder(ss);
	
	ofBuffer buffer;
	decoder >> buffer;
    
    return buffer;
}