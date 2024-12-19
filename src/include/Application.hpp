#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Window.hpp"
#include "Device.hpp"
#include "SwapChain.hpp"
#include "Pipeline.hpp"
#include "Model.hpp"

#include <memory>

class Application {
private:
	const int WIDTH = 800;
	const int HEIGHT = 600;
	const char* APPLICATION_NAME = "Title";
	const char* ENGINE_NAME = "Stellar Nursery Engine";

	Window mWindow{ WIDTH, HEIGHT, APPLICATION_NAME };
	Device mDevice{ mWindow };
	SwapChain mSwapChain{ mDevice, mWindow.getExtent() };
	std::unique_ptr<Pipeline> mPipeline;

	VkPipelineLayout mPipelineLayout;
	std::vector<VkCommandBuffer> mCommandBuffers;

	std::unique_ptr<Model> mModel;

	void loadModels();
	void createPipelineLayout();
	void createPipeline();
	void createCommandBuffers();

	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

	void drawFrame();

public:
	Application();
	~Application();

	void run();

	Application(const Application& other) = delete;
	Application& operator=(const Application& other) = delete;
	Application(Application&& other) = delete;
	Application& operator=(Application&& other) = delete;
};

#endif // APPLICATION_HPP
