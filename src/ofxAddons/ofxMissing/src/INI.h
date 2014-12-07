#pragma once

#include <stdint.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct INIEntry {
	INIEntry(string sKey, string sVal, string sSection = "")
		:key(sKey)
		,value(sVal)
		,section(sSection) 
	{
	}
	string key;
	string value;
	string section;
	
};

enum INITypes {
 	 INI_COMMENT
	,INI_NEW_LINE
	,INI_ENTRY
};

struct INISortedEntry {
	INISortedEntry(string sValue, int nType)
		:value(sValue)
		,type(nType)
	{
	}
	string value;
	int type;
};

class INI {
public:	
	INI();
	
	// storage
	bool load(string sFile);
	bool save(string sFile);
	
	// retrieve settings
	string	getString(string sKey, string sDefault = "");
	int		getInt(string sKey, int nDefault = 0);
	float	getFloat(string sKey, float nDefault = 0.0f);
	double	getDouble(string sKey, double nDefault = 0.0);
	bool	getBool(string sKey, bool bDefault = false);


	// store settings.
	void	setString(string sKey, string sValue);
	void	setInt(string sKey, int nValue);
	void	setFloat(string sKey, float nValue);
	void	setDouble(string sKey, double nValue);
	void	setBool(string sKey, bool nValue);
	
	// helpers
	// -------------------------------------------------------------------------
	inline bool get(string sKey, string& rFound) {
		map<string, INIEntry*>::iterator it = dict.find(sKey);
		if(it == dict.end()) {
			return false;
		}
		rFound = (*it->second).value;
		return true;
	}
	
	template<typename T>
	T convert(string sIn) {
		T result;
		stringstream ss;
		ss << sIn;
		ss >> result;
		return result;
	}
	
	template<typename T>
	void setValue(string sKey, T v) {
		INIEntry* e = getEntry(sKey);
		if(e == NULL) {
			cout << "error: entry: '" << sKey << "' not found in dictionary" << endl;
			return;
		}
	
		stringstream ss;
		ss << v;
		ss >> e->value;
	}

	inline INIEntry* getEntry(string sKey) {
		map<string, INIEntry*>::iterator it = dict.find(sKey);
		if(it == dict.end()) {
			return NULL;
		}
		return it->second;
	}
	
	friend ostream& operator<<(ostream& os, const INI& ini);
	
private: 
	map<string, INIEntry*> dict;
	vector<INISortedEntry*> sorted_entries;
};


inline ostream& operator<<(ostream& os, const INI& ini) {
	string curr_section = "";
	vector<INISortedEntry*>::const_iterator it = ini.sorted_entries.begin();
	while(it != ini.sorted_entries.end()) {
		const INISortedEntry* entry = (*it);
		if(entry->type == INI_ENTRY) {
			map<string, INIEntry*>::const_iterator map_it = ini.dict.find(entry->value);
			if(map_it == ini.dict.end()) {
				cout << "error: trying to store ini but key is removed: '" << (*it)->value << endl;
				++it;
				continue;
			}
			INIEntry& e = (*map_it->second);
			if(curr_section != e.section) {
				curr_section = e.section;
				os << "[" << e.section << "]" << endl;
			}
			os << e.key << "=" << e.value << endl;
		}
		else if(entry->type == INI_COMMENT) {
			os << entry->value << endl;
		}
		else if(entry->type == INI_NEW_LINE) {
			os << endl;
		}
		++it;
	}
}