#pragma once

#include "ofMain.h"
#include <set>
#ifdef __cplusplus
	extern "C" {
#endif

void trimInP(string& str);
void setFrameRateAsWindowTitle();
void setupOF(int fps = 60); // 60 FPS, vertical sync, dark background
bool createDirectory(string dir, bool relativeToDataDir = true, bool createSubDirectories = true);
bool fileExists(string path, bool relativeToDataDir = true);
std::set<string> getFiles(string filePathWithGlob, bool relativeToDataDir = true);
string md5(string input);
string gaStringReplace(string input, string searchStr, string replaceStr);

#ifdef __cplusplus
	}
#endif