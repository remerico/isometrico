#ifndef STRUTILS_H
#define STRUTILS_H

#include <string>
#include <sstream>
#include <iterator>
#include "b64/decode.h"

class StrUtils {

public:
	static std::string getString(const char* str) {
		return std::string(str != NULL ? str : "");
	}
	
	static void convertFromBase64(const std::string& input, std::string& output) {
		
		std::stringstream instream;
		base64::decoder dec;
		
		output.reserve(1024);  // reserve extra memory for faster allocation later
		
		instream << input;
		dec.decode(instream, output);
		
	}

	static void replace(std::string& str, const std::string& old, const std::string& newstr) {
		size_t pos = 0;

		while((pos = str.find(old, pos)) != std::string::npos) {
			str.replace(pos, old.length(), newstr);
			pos += newstr.length();
		}
	}

	static std::vector<std::string> split(const std::string& str, const std::string& delim) {

		using namespace std;

		vector<string> tokens;

		string::size_type lastPos = str.find_first_not_of(delim, 0);
		string::size_type pos     = str.find_first_of(delim, lastPos);

		while (string::npos != pos || string::npos != lastPos) {
			tokens.push_back(str.substr(lastPos, pos - lastPos));
			lastPos = str.find_first_not_of(delim, pos);
			pos = str.find_first_of(delim, lastPos);
		}

		return tokens;
	}

	static std::string combine(const std::vector<std::string>& strlist) {
		std::stringstream sstr;
		for (unsigned int i = 0; i < strlist.size(); ++i) sstr << strlist.at(i);
		return sstr.str();
	}

	
};

#endif