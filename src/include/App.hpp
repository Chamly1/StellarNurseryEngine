#include "Window.hpp"
#include "Device.hpp"
#include "Pipeline.hpp"

#include <vector>
#include <optional>

class App {
public:
	void run();

private:
	const int WIDTH = 800;
	const int HEIGHT = 600;
	const char* APPLICATION_NAME = "Title";
	const char* ENGINE_NAME = "Stellar Nursery Engine";

	Window mWindow{WIDTH, HEIGHT, APPLICATION_NAME};
	Device mDevice{ mWindow };
	Pipeline mPipeline{mDevice, "./resources/shaders/triangle.vert.spv", "./resources/shaders/triangle.frag.spv", Pipeline::getDefaultPipelineConfigInfo(static_cast<uint32_t>(WIDTH), static_cast<uint32_t>(HEIGHT))};

	
	

	
	VkPipelineLayout pipelineLayout;
	

	

	
	VkCommandBuffer commandBuffer;

	

	void initWindow();
	

	

	
	void createGraphicsPipeline();

	

	
	void createCommandBuffer();
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	

	void initVulkan();

	void drawFrame();

	void mainLoop();
	void cleanup();
};