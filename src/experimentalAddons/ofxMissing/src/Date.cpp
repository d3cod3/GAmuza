#include "Date.h"

// returns something like: 2011.06.19.22.31
string getDateTimeAsString(string sFormat) {
	Poco::LocalDateTime now;
	string str = DateTimeFormatter::format(now, sFormat);	
	return str;
};