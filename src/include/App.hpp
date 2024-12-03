#include "Window.hpp"
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
	Pipeline mPipeline{"./resources/shaders/triangle.vert.spv", "./resources/shaders/triangle.frag.spv"};

	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	std::vector<VkImageView> swapChainImageViews;

	VkRenderPass renderPass;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	std::vector<VkFramebuffer> swapChainFramebuffers;

	
	VkCommandBuffer commandBuffer;

	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
	VkFence inFlightFence;

	void initWindow();
	

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	void createSwapChain();

	void createImageViews();

	void createRenderPass();

	VkShaderModule createShaderModule(const std::vector<char>& code);
	void createGraphicsPipeline();

	void createFramebuffers();

	
	void createCommandBuffer();
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	void createSuncObjects();

	void initVulkan();

	void drawFrame();

	void mainLoop();
	void cleanup();
};