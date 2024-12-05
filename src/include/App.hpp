#include "Window.hpp"
#include "Device.hpp"
#include "Pipeline.hpp"

#include <vector>
#include <optional>

class App {
public:
	void run();

private:
	

	
	

	
	

	

	void initWindow();
	

	

	
	void createGraphicsPipeline();

	

	
	void createCommandBuffer();
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	

	void initVulkan();

	void drawFrame();

	void mainLoop();
	void cleanup();
};