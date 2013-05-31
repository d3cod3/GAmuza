#pragma once

#include "Poco/DateTime.h"
#include "Poco/LocalDateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeParser.h"
#include <string>

using namespace std;
//using Poco::LocalDateTime;
using Poco::DateTime;
using Poco::DateTimeFormat;
using Poco::DateTimeFormatter;
using Poco::DateTimeParser;

#ifdef __cplusplus
	extern "C" {
#endif

// returns something like: 2011.06.19.22.31
string getDateTimeAsString(string sFormat = "%Y.%m.%d.%H.%M");

#ifdef __cplusplus
	}
#endif