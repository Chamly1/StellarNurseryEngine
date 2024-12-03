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

	VkSemaphore mImageAvailableSemaphore;
	VkSemaphore mRenderFinishedSemaphore;
	VkFence mInFlightFence;

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	void createSwapChain();
	void createImageViews();
	void createRenderPass();
	void createFramebuffers();
	void createSyncObjects();

public:
	SwapChain(Device& device, VkExtent2D windowExtent);
	~SwapChain();

	SwapChain(const SwapChain& other) = delete;
	SwapChain& operator=(const SwapChain& other) = delete;
	SwapChain(SwapChain&& other) = delete;
	SwapChain& operator=(SwapChain&& other) = delete;
};

#endif // SWAPCHAIN_HPP
