#include "Window.hpp"

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

// TODO: stub method
GLFWwindow* Window::getWindow() {
	return mWindow;
}
