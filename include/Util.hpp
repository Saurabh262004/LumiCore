#ifndef UTIL_HPP
#define UTIL_HPP

#include <fstream>
#include <sstream>
#include <string>

class Util {
public:
	static std::string readFile(const std::string& path);
};

#endif