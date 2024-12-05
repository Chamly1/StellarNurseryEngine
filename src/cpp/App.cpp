#include "App.hpp"
#include "VulkanUtils.hpp"
#include "utils.hpp"

#include <stdexcept>
#include <iostream>
#include <set>
#include <algorithm>

void App::run() {
	initWindow();
	initVulkan();
	mainLoop();
	cleanup();
}

void App::initWindow() {
	
}



void App::createGraphicsPipeline() {
	
	std::vector<VkDynamicState> dynamicStates = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};
	VkPipelineDynamicStateCreateInfo dynamicState{};
	dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
	dynamicState.pDynamicStates = dynamicStates.data();


	
}



void App::createCommandBuffer() {
	
}

void App::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) {
	
}



void App::initVulkan() {
	
	createGraphicsPipeline();
	
	createCommandBuffer();
}

void App::drawFrame() {
	
}

void App::mainLoop() {
	
}

void App::cleanup() {

}
