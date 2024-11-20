#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <vector>
#include <optional>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;

	bool isComplete();
};

class App {
public:
	void run();

private:
	GLFWwindow* window;
	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;
	const char* APPLICATION_NAME = "Title";
	const char* ENGINE_NAME = "Stellar Nursery Engine";

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	#ifdef NDEBUG
	const bool enableValidationLayers = false;
	#else
	const bool enableValidationLayers = true;
	#endif

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);

	bool checkValidationLayerSupport();
	std::vector<const char*> getRequiredExtensions();
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	void initWindow();
	void createInstance();
	void setupDebugMessenger();
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	bool isDeviceSuitable(VkPhysicalDevice device);
	void pickPhysicalDevice();
	void initVulkan();
	void mainLoop();
	void cleanup();
};