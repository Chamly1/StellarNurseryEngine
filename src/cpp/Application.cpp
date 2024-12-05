#include "Application.hpp"

void Application::createPipelineLayout() {
	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 0;
	pipelineLayoutInfo.pSetLayouts = nullptr;
	pipelineLayoutInfo.pushConstantRangeCount = 0;
	pipelineLayoutInfo.pPushConstantRanges = nullptr;

	if (vkCreatePipelineLayout(mDevice.device(), &pipelineLayoutInfo, nullptr, &mPipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create pipeline layout!");
	}
}

void Application::createPipeline() {
	PipelineConfigInfo pipelineConfig = Pipeline::getDefaultPipelineConfigInfo(mSwapChain.getWidth(), mSwapChain.getHeight());
	pipelineConfig.renderPass = mSwapChain.getRenderPass();
	pipelineConfig.pipelineLayout = mPipelineLayout;

	mPipeline = std::make_unique<Pipeline>(
		mDevice,
		"./resources/shaders/triangle.vert.spv",
		"./resources/shaders/triangle.frag.spv",
		pipelineConfig);
}

void Application::createCommandBuffer() {
	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = mDevice.getCommandPool();
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;

	if (vkAllocateCommandBuffers(mDevice.device(), &allocInfo, &mCommandBuffer) != VK_SUCCESS) {
		throw std::runtime_error("Failed to allocate command buffers!");
	}
}

void Application::recordCommandBuffer(uint32_t imageIndex) {
	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = 0; // Optional
	beginInfo.pInheritanceInfo = nullptr; // Optional

	if (vkBeginCommandBuffer(mCommandBuffer, &beginInfo) != VK_SUCCESS) {
		throw std::runtime_error("Failed to begin recording command buffer!");
	}

	VkRenderPassBeginInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = mSwapChain.getRenderPass();
	renderPassInfo.framebuffer = mSwapChain.getFrameBuffer(imageIndex);
	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = mSwapChain.getSwapChainExtent();
	VkClearValue clearColor = VkClearValue{ VkClearColorValue{ { 0.0f, 0.0f, 0.0f, 1.0f } } };
	renderPassInfo.clearValueCount = 1;
	renderPassInfo.pClearValues = &clearColor;

	vkCmdBeginRenderPass(mCommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
	mPipeline->bind(mCommandBuffer);

	/*VkViewport viewport = VkViewport();
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = mSwapChain.getWidth();
	viewport.height = mSwapChain.getHeight();
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	vkCmdSetViewport(mCommandBuffer, 0, 1, &viewport);

	VkRect2D scissor = VkRect2D();
	scissor.offset = { 0, 0 };
	scissor.extent = mSwapChain.getSwapChainExtent();
	vkCmdSetScissor(mCommandBuffer, 0, 1, &scissor);*/

	vkCmdDraw(mCommandBuffer, 3, 1, 0, 0);
	vkCmdEndRenderPass(mCommandBuffer);

	if (vkEndCommandBuffer(mCommandBuffer) != VK_SUCCESS) {
		throw std::runtime_error("Failed to record command buffer!");
	}
}

void Application::drawFrame() {
	uint32_t imageIndex;
	VkResult res = mSwapChain.acquireNextImage(&imageIndex);
	if (res != VK_SUCCESS && res != VK_SUBOPTIMAL_KHR) {
		throw std::runtime_error("Failed to aquire swap chain image!");
	}

	vkResetCommandBuffer(mCommandBuffer, 0);
	recordCommandBuffer(imageIndex);

	res = mSwapChain.submitCommandBuffer(&mCommandBuffer, imageIndex);
	if (res != VK_SUCCESS) {
		throw std::runtime_error("Failed to present swap chain image!");
	}
}

Application::Application() {
	createPipelineLayout();
	createPipeline();
	createCommandBuffer();
}

Application::~Application() {
	vkDestroyPipelineLayout(mDevice.device(), mPipelineLayout, nullptr);
}

void Application::run() {
	while (!mWindow.shouldClose()) {
		glfwPollEvents();
		drawFrame();
	}

	vkDeviceWaitIdle(mDevice.device());
}
