#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include <string>

class Pipeline {
private:

public:

	Pipeline(const std::string& vertFilepath, const std::string& fragFilepath);

	Pipeline(const Pipeline& other) = delete;
	Pipeline& operator=(const Pipeline& other) = delete;
	Pipeline(Pipeline&& other) = delete;
	Pipeline& operator=(Pipeline&& other) = delete;
};

#endif // PIPELINE_HPP
