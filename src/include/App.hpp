#include <GLFW/glfw3.h>

class App {
public:
	void run();

private:
	GLFWwindow* window;
	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;
	const char* TITLE = "Title";

	void initWindow();
	void initVulkan();
	void mainLoop();
	void cleanup();
};