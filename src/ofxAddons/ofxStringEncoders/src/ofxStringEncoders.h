#ifndef HTMLENTITIESH
#define HTMLENTITIESH
#include <string>
#include <iostream>
#include <map>
class ofxStringEncoders{
public:
    
	static void writeUTF8 (
		std::ostream & Out,
		unsigned int Ch
	);
	static void unquoteHTML(
		std::istream & In,
		std::ostream & Out
	);
};
#endif