#include "RecursiveFileList.h"
RecursiveFileList::RecursiveFileList() 
:max_dept(5)
{
}


vector<string> RecursiveFileList::getFiles(string sDir, string sExt, int nMaxFiles) {
	file_count = 0;
	max_files = nMaxFiles;
	vector<string> found_files;
	recurse(found_files, sDir, sExt, 0);
	return found_files;
}

// sListDir MUST HAVE A SLASH AT THE END!	
void RecursiveFileList::recurse(vector<string>&rFiles, string sListDir, string sExt, int nDepth) {
	if(file_count > max_files) {
		return;
	}
	
	// get files from dir.
	File curr_file(sListDir);
	vector<string> new_files;
	curr_file.list(new_files);
	
	vector<string>::iterator it = new_files.begin();
	while(it != new_files.end()) {
		string path = sListDir +*it;
		File fp(path);
		try {
			if(fp.isDirectory()) {	
				path += "/";
				recurse(rFiles, path, sExt, nDepth + 1);
			}
			else {
				Path p(path);
				if(p.getExtension() == sExt){
					rFiles.push_back(path);
					++file_count;
				}
			}
		}
		catch(...) {
			cout << "Got exception... " << endl;
		}
		++it;
	}

}