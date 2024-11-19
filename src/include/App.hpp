#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

class App {
public:
	void run();

private:
	GLFWwindow* window;
	VkInstance instance;
	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;
	const char* APPLICATION_NAME = "Title";
	const char* ENGINE_NAME = "Stellar Nursery Engine";

	void initWindow();
	void createInstance();
	void initVulkan();
	void mainLoop();
	void cleanup();
};