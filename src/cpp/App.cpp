#include "App.hpp"

void App::run() {
	initWindow();
	initVulkan();
	mainLoop();
	cleanup();
}

void App::initWindow() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);
}

void App::initVulkan() {

}

void App::mainLoop() {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}
}

void App::cleanup() {
	glfwDestroyWindow(window);

	glfwTerminate();
}
