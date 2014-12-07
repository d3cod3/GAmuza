#include "INI.h"

// INI
// -----------------------------------------------------------------------------
INI::INI() {
}

bool INI::load(string sFile) {
	ifstream ifs(sFile.c_str());
	if(!ifs.is_open()) {
		cout << "error: cannot load ini file:" << sFile << endl;
		return false;
	}
	string line;
	string section;
	while(getline(ifs,line)) {
		
		// empty line.
		if(line.size() == 0) {
			INISortedEntry* se = new INISortedEntry("", INI_NEW_LINE);
			sorted_entries.push_back(se);
			continue;
		}
			
		// get key
		string key;
		int key_end = 0;
		for(int i = 0; i < line.size(); ++i) {
			if(line[i] == '=') {
				key_end = i+1;
				break;
			}
			else {
				if(line[i] != ' ') {
					key.push_back(line[i]);
				}
			}
		}
		
		// is it a comment?
		if(key.at(0) == '#') {
			INISortedEntry* sorted_entry = new INISortedEntry(line, INI_COMMENT);
			sorted_entries.push_back(sorted_entry);
			continue;
		}
		
		// is key a section?
		if(key.at(0) == '[') {
			section = "";
			for(int i = 0; i < key.size(); ++i) {
				if(key[i] != '[' && key[i] != ']')  {
					section.push_back(key[i]);
				}
			}
			continue;
		}
		
		// get value.
		string val;
		for(int i = key_end; i < line.size(); ++i) {
			if(line[i] == '\r' || line[i] == '\n') {
				break;
			}
			val.push_back(line[i]);
		}
			

		// trim 
		string key_copy = key;
		if(section != "") {
			key = "." +key;
		}
		
		string dict_key = section + key;
		INIEntry* entry = new INIEntry(key_copy, val, section);
		dict.insert(pair<string,INIEntry*>(dict_key,entry));
		INISortedEntry* sorted_entry = new INISortedEntry(dict_key, INI_ENTRY);
		sorted_entries.push_back(sorted_entry);
	}
	return true;
}

bool INI::save(string sFile) {
	ofstream ofs(sFile.c_str(), std::ios::out | std::ios::trunc);
	if(!ofs.is_open()) {
		cout << "error: cannot open file '" << sFile << "' for writing" << endl;
		return false;
	}
	ofs << *this;
	ofs.flush();
	ofs.close();
	return true;
}

string INI::getString(string sKey, string sDefault) {
	string val;
	if(!get(sKey,val)) {
		cout << sKey << " not found" << endl;
		return sDefault;
	}
	return val;
}

int INI::getInt(string sKey, int nDefault) {
	string val;
	if(!get(sKey,val)) {
		return nDefault;
	}
	return convert<int>(val);
}

float INI::getFloat(string sKey, float nDefault) {
	string val;
	if(!get(sKey,val)) {
		return nDefault;
	}
	convert<float>(val);
}

double INI::getDouble(string sKey, double nDefault) {
	string val;
	if(!get(sKey,val)) {
		return nDefault;
	}
	convert<double>(val);
}

bool INI::getBool(string sKey, bool bDefault) {
	string val;
	if(!get(sKey,val)) {
		return bDefault;
	}
	
	if(val == "n" || val == "N" || val == "no" || val == "NO" || val == "0" || val == "false" || val == "FALSE") {
		return false;
	}
	if(val == "y" || val == "Y" || val == "yes" || val == "YES" || val == "1" || val == "true" || val == "TRUE") {
		return true;
	}
	return bDefault;
}

void INI::setString(string sKey, string sValue) {
	INIEntry* e = getEntry(sKey);
	if(e == NULL) {
		cout << "error: entry: '" << sKey << "' not found in dictionary" << endl;
		return;
	}
	e->value = sValue;
}

void INI::setInt(string sKey, int nValue) {
	setValue<int>(sKey,nValue);
}

void INI::setFloat(string sKey, float nValue) {
	setValue<float>(sKey, nValue);
}

void INI::setDouble(string sKey, double nValue) {
	setValue<double>(sKey, nValue);
}

void INI::setBool(string sKey, bool nValue) {
	setValue<bool>(sKey, nValue);
}