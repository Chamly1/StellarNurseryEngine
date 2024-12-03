#include "Window.hpp"

#include <stdexcept>

Window::Window(int w, int h, std::string name) : mWindowName(name), mWidth(w), mHeight(h) {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	mWindow = glfwCreateWindow(mWidth, mHeight, mWindowName.c_str(), nullptr, nullptr);
}

Window::~Window() {
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(mWindow);
}

void Window::createSurface(VkInstance instance, VkSurfaceKHR* surface) {
	if (glfwCreateWindowSurface(instance, mWindow, nullptr, surface) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create window surface!");
	}
}

// TODO: stub method
GLFWwindow* Window::getWindow() {
	return mWindow;
}
