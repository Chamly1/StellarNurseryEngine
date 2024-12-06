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
	std::unique_ptr<PipelineConfigInfo> pipelineConfig = Pipeline::getDefaultPipelineConfigInfo(mSwapChain.getWidth(), mSwapChain.getHeight());
	pipelineConfig->renderPass = mSwapChain.getRenderPass();
	pipelineConfig->pipelineLayout = mPipelineLayout;

	mPipeline = std::make_unique<Pipeline>(
		mDevice,
		"./resources/shaders/triangle.vert.spv",
		"./resources/shaders/triangle.frag.spv",
		*pipelineConfig);
}

void Application::createCommandBuffers() {
	mCommandBuffers.resize(mSwapChain.MAX_FRAMES_IN_FLIGHT);

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = mDevice.getCommandPool();
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = static_cast<uint32_t>(mCommandBuffers.size());

	if (vkAllocateCommandBuffers(mDevice.device(), &allocInfo, mCommandBuffers.data()) != VK_SUCCESS) {
		throw std::runtime_error("Failed to allocate command buffers!");
	}
}

void Application::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) {
	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = 0; // Optional
	beginInfo.pInheritanceInfo = nullptr; // Optional

	if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
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

	vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
	mPipeline->bind(commandBuffer);

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

	vkCmdDraw(commandBuffer, 3, 1, 0, 0);
	vkCmdEndRenderPass(commandBuffer);

	if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
		throw std::runtime_error("Failed to record command buffer!");
	}
}

void Application::drawFrame() {
	uint32_t imageIndex;
	VkResult res = mSwapChain.acquireNextImage(&imageIndex);
	if (res != VK_SUCCESS && res != VK_SUBOPTIMAL_KHR) {
		throw std::runtime_error("Failed to aquire swap chain image!");
	}

	// TODO: mey be should pre-record command buffers during initialization,
	// and only update dynamic states or descriptors as needed
	uint32_t currentFrame = mSwapChain.getCurrentFrame();
	vkResetCommandBuffer(mCommandBuffers[currentFrame], 0);
	recordCommandBuffer(mCommandBuffers[currentFrame], imageIndex);

	res = mSwapChain.submitCommandBuffer(&mCommandBuffers[currentFrame], imageIndex);
	if (res != VK_SUCCESS) {
		throw std::runtime_error("Failed to present swap chain image!");
	}
}

Application::Application() {
	createPipelineLayout();
	createPipeline();
	createCommandBuffers();
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
