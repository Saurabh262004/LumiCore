#include <iostream>
#include "../external/glad/glad.h"
#include <GLFW/glfw3.h>

#include "Window.hpp"

Window::Window(int width, int height, bool fullscreen) {
	this->width = width;
	this->height = height;
	this->fullscreen = fullscreen;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (fullscreen) {
		window = glfwCreateWindow(
			width,
			height,
			"OpenGL",
			glfwGetPrimaryMonitor(),
			nullptr
		);
	} else {
		window = glfwCreateWindow(
			width,
			height,
			"OpenGL",
			nullptr,
			nullptr
		);
	}

	if (!window) {
		std::cerr << "Failed to create window\n";
		window = nullptr;
	} else {
		if (!initOpenGL()) clean();
	}
}

bool Window::initOpenGL() {
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD\n";
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glfwSwapInterval(1);

	glViewport(0, 0, width, height);

	return true;
}

void Window::setWindowPosCallback(GLFWwindowposfun callback) {
	glfwSetWindowPosCallback(window, callback);
}

void Window::setWindowSizeCallback(GLFWwindowsizefun callback) {
	glfwSetWindowSizeCallback(window, callback);
}

void Window::setWindowCloseCallback(GLFWwindowclosefun callback) {
	glfwSetWindowCloseCallback(window, callback);
}

void Window::setWindowRefreshCallback(GLFWwindowrefreshfun callback) {
	glfwSetWindowRefreshCallback(window, callback);
}

void Window::setWindowFocusCallback(GLFWwindowfocusfun callback) {
	glfwSetWindowFocusCallback(window, callback);
}

void Window::setWindowIconifyCallback(GLFWwindowiconifyfun callback) {
	glfwSetWindowIconifyCallback(window, callback);
}

void Window::setWindowMaximizeCallback(GLFWwindowmaximizefun callback) {
	glfwSetWindowMaximizeCallback(window, callback);
}

void Window::setFramebufferSizeCallback(GLFWframebuffersizefun callback) {
	glfwSetFramebufferSizeCallback(window, callback);
}

void Window::setWindowContentScaleCallback(GLFWwindowcontentscalefun callback) {
	glfwSetWindowContentScaleCallback(window, callback);
}

void Window::setKeyCallback(GLFWkeyfun callback) {
	glfwSetKeyCallback(window, callback);
}

void Window::setCharCallback(GLFWcharfun callback) {
	glfwSetCharCallback(window, callback);
}

void Window::setCursorPosCallback(GLFWcursorposfun callback) {
	glfwSetCursorPosCallback(window, callback);
}

void Window::setCursorEnterCallback(GLFWcursorenterfun callback) {
	glfwSetCursorEnterCallback(window, callback);
}

void Window::setMouseButtonCallback(GLFWmousebuttonfun callback) {
	glfwSetMouseButtonCallback(window, callback);
}

void Window::setScrollCallback(GLFWscrollfun callback) {
	glfwSetScrollCallback(window, callback);
}

void Window::setDropCallback(GLFWdropfun callback) {
	glfwSetDropCallback(window, callback);
}

void Window::loop() {
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.15f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	clean();
}

void Window::clean() {
	if (window) glfwDestroyWindow(window);

	glfwTerminate();
}
