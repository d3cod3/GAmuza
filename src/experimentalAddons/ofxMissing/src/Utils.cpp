#include "Utils.h"

#include <Poco/File.h>
#include <Poco/Path.h>
#include <Poco/Exception.h>
#include <Poco/String.h>
#include <Poco/Glob.h>
#include <Poco/DigestStream.h>
#include <Poco/MD5Engine.h>

using Poco::File;
using Poco::Exception;
using Poco::Glob;
using Poco::trim;
using Poco::trimInPlace;
using Poco::DigestOutputStream;
using Poco::DigestEngine;
using Poco::MD5Engine;

void setFrameRateAsWindowTitle() {
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

void trimInP(string& str) {
	trimInPlace(str);
}

// 60 FPS, vertical sync, dark background
void setupOF(int fps) {
	ofSetFrameRate(fps);
	if(fps <= 60) {
		ofSetVerticalSync(true);
	}
	ofBackground(33,33,33);
}

// create a directory if it doesnt exist yet.
bool createDirectory(string dir, bool relativeToDataDir, bool createSubDirectories) {
	try {
		trim(dir);
		if(relativeToDataDir) {
			dir = ofToDataPath(dir,true);
		}
		Poco::File f(dir);
		try {
			if(f.isDirectory()) { // throws!
				return true;
			}
		}
		catch(...) {
			if(createSubDirectories) {
				f.createDirectories();
			}
			else {
				f.createDirectory();
			}
		}
	}
	catch(Poco::FileException& ex) {
		printf("Cannot create directory: '%s' reason:'%s'\n"
				,dir.c_str()
				,ex.displayText().c_str()
		);
		return false;
	}
	return true;
}

// tiny helper to check if a file exists.
bool fileExists(string path, bool relativeToDataDir) {
	bool ex = false;	
	try {
		if(relativeToDataDir) {
			path = ofToDataPath(path,true);
		}
		Poco::File f(path);
		ex = f.exists();
	}
	catch(Poco::FileException& ex) {
		printf("Cannot create directory: '%s' reason:'%s'\n"
				,path.c_str()
				,ex.displayText().c_str()
		);
		return false;
	}
	return ex;
}

// Get Files by a globber filePathWithGlob example: /data/dir/filename* 
set<string> getFiles(string filePathWithGlob, bool relativeToDataDir) {
	if(relativeToDataDir) {
		filePathWithGlob = ofToDataPath(filePathWithGlob,true);
	}
	set<string> files;
	try {
		Glob::glob(filePathWithGlob, files);
	}
	catch(...) {
		printf("Error while globbing...\n");
	}
	return files;
}

// string to md5
string md5(string input) {
	string hash;
	MD5Engine md5_engine;
	DigestOutputStream ostr(md5_engine);
	ostr << input;
	ostr.flush();
	const DigestEngine::Digest& digest = md5_engine.digest();
	hash = DigestEngine::digestToHex(digest);
	return hash;
}

int gaStringReplace(string& input, string searchStr, string replaceStr){
    
    int qty = 0;
    
	size_t uPos = 0; 
	size_t uFindLen = searchStr.length(); 
	size_t uReplaceLen = replaceStr.length();
    
	if( uFindLen == 0 ){
		return 0;
	}
    
	for( ;(uPos = input.find( searchStr, uPos )) != std::string::npos; ){
		input.replace( uPos, uFindLen, replaceStr );
		uPos += uReplaceLen;
        qty++;
	}
    
    return qty;
}