#ifndef SWAPCHAIN_HPP
#define SWAPCHAIN_HPP

#include "Device.hpp"

#include "vulkan/vulkan.hpp"

class SwapChain {
private:
	VkFormat mSwapChainImageFormat;
	VkExtent2D mSwapChainExtent;

	std::vector<VkFramebuffer> mSwapChainFramebuffers;
	VkRenderPass mRenderPass;

	std::vector<VkImage> mSwapChainImages;
	std::vector<VkImageView> mSwapChainImageViews;

	Device& mDevice;
	VkExtent2D mWindowExtent;

	VkSwapchainKHR mSwapChain;

	std::vector<VkSemaphore> mImageAvailableSemaphores;
	std::vector<VkSemaphore> mRenderFinishedSemaphores;
	std::vector<VkFence> mInFlightFences;

	uint32_t mCurrentFrame = 0;

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	void createSwapChain();
	void createImageViews();
	void createRenderPass();
	void createFramebuffers();
	void createSyncObjects();

public:
	static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

	SwapChain(Device& device, VkExtent2D windowExtent);
	~SwapChain();

	uint32_t getWidth();
	uint32_t getHeight();
	VkFramebuffer getFrameBuffer(int index);
	VkRenderPass getRenderPass();
	VkExtent2D getSwapChainExtent();
	uint32_t getCurrentFrame();

	VkResult acquireNextImage(uint32_t* imageIndex);
	VkResult submitCommandBuffer(const VkCommandBuffer* buffer, uint32_t imageIndex);

	SwapChain(const SwapChain& other) = delete;
	SwapChain& operator=(const SwapChain& other) = delete;
	SwapChain(SwapChain&& other) = delete;
	SwapChain& operator=(SwapChain&& other) = delete;
};

#endif // SWAPCHAIN_HPP
