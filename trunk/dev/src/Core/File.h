#ifndef GAME_FILE_H
#define GAME_FILE_H

#include "Defines.h"

namespace game {

class File {

public:
	static std::string getPath(std::string path) {
		std::string str = path;

		replaceBackslash(str);
		str = str.substr(0, str.rfind('/') + 1);

		return str;
	}

	static void replaceBackslash(std::string& str) {
		size_t pos = 0;
		while((pos = str.find("\\", pos)) != std::string::npos) {
			str.replace(pos, 1, "/");
			++pos;
		}
	}
	
	static std::string combinePath(std::string path1, std::string path2) {

		std::vector<std::string> srcpath;
		std::vector<std::string> destpath;
		std::stringstream sstr;
		int count;

		replaceBackslash(path1);
		replaceBackslash(path2);
		
		srcpath = StrUtils::split(path1, "/");
		destpath = StrUtils::split(path2, "/");

		count = destpath.size();
		for (int i = 0; i < count; ++i) {

			std::string p = destpath.at(i);

			if (p.compare("..") == 0) srcpath.pop_back();
			else if (p.compare(".") == 0) {  }
			else srcpath.push_back(p);

		}

				
		count = srcpath.size();
		for (int i = 0; i < count; ++i) {
			sstr << srcpath.at(i);
			if (i < count - 1) sstr << "/";
		}
		return sstr.str();

	}

};


}

#endif