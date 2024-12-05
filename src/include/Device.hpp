#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "Window.hpp"

#include <optional>
#include <vector>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete();
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

class Device {
private:
#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif
	const std::vector<const char*> mValidationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};
	const std::vector<const char*> mDeviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	VkInstance mInstance;
	VkDebugUtilsMessengerEXT mDebugMessenger;
	VkSurfaceKHR mSurface;

	VkPhysicalDevice mPhysicalDevice = VK_NULL_HANDLE;
	VkDevice mDevice;

	VkQueue mGraphicsQueue;
	VkQueue mPresentQueue;

	VkCommandPool mCommandPool;

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);

	bool checkValidationLayerSupport();
	std::vector<const char*> getRequiredExtensions();
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	void createInstance();
	void setupDebugMessenger();
	void createSurface(Window& window);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	bool isDeviceSuitable(VkPhysicalDevice device);
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createCoomandPool();

public:
	Device(Window& window);
	~Device();

	VkDevice device(); // TODO: rename to getDevice()
	VkSurfaceKHR surface(); // TODO: rename to getSurface()
	VkCommandPool getCommandPool();
	VkQueue getGraphicsQueue();
	VkQueue getPresentQueue();

	SwapChainSupportDetails getSwapChainSupport();
	QueueFamilyIndices findPhysicalQueueFamilies();

	Device(const Device& other) = delete;
	Device& operator=(const Device& other) = delete;
	Device(Device&& other) = delete;
	Device& operator=(Device&& other) = delete;
};

#endif // DEVICE_HPP
