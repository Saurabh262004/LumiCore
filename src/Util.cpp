#include <fstream>
#include <sstream>
#include <string>

#include <Util.hpp>

std::string Util::readFile(const std::string& path) {
	std::ifstream file(path);

	if (!file.is_open()) {
		throw std::runtime_error("Failed to open " + path);
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	return buffer.str();
}
