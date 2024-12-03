#ifndef WINDOW_HPP
#define WINDOW_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

class Window {
private:
	GLFWwindow* mWindow;
	std::string mWindowName;

	const int mWidth;
	const int mHeight;

public:
	Window(int w, int h, std::string name);
	~Window();

	bool shouldClose();
	void createSurface(VkInstance instance, VkSurfaceKHR *surface);
	// TODO: stub method
	GLFWwindow* getWindow();
	VkExtent2D getExtent();

	Window(const Window& other) = delete;
	Window& operator=(const Window& other) = delete;
	Window(Window&& other) = delete;
	Window& operator=(Window&& other) = delete;
};

#endif // WINDOW_HPP
