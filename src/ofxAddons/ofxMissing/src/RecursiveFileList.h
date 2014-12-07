#pragma once

#include <Poco/Path.h>
#include <Poco/File.h>

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using Poco::File;
using Poco::Path;

class RecursiveFileList {
public:
	RecursiveFileList();
	vector<string> getFiles(string sDir, string sExt, int nMaxFiles = 100);
private:
	void recurse(vector<string>&rFiles, string sListDir, string sExt, int nDepth = 0);
	int max_dept;
	int file_count;
	int max_files;
};