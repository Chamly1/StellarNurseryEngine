#include "Pipeline.hpp"
#include "utils.hpp"

Pipeline::Pipeline(const std::string& vertFilepath, const std::string& fragFilepath) {
	std::vector<char> vertCode = readFile(vertFilepath);
	std::vector<char> fragCode = readFile(fragFilepath);
}
