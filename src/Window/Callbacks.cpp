#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Util.hpp>
#include <Window.hpp>

void Window::setInternalCallbacks() {
	glfwSetWindowPosCallback(window, staticWindowPosCallback);
	glfwSetWindowSizeCallback(window, staticWindowSizeCallback);
	glfwSetWindowCloseCallback(window, staticWindowCloseCallback);
	glfwSetWindowRefreshCallback(window, staticWindowRefreshCallback);
	glfwSetWindowFocusCallback(window, staticWindowFocusCallback);
	glfwSetWindowIconifyCallback(window, staticWindowIconifyCallback);
	glfwSetWindowMaximizeCallback(window, staticWindowMaximizeCallback);
	glfwSetFramebufferSizeCallback(window, staticFramebufferSizeCallback);
	glfwSetWindowContentScaleCallback(window, staticWindowContentScaleCallback);
	glfwSetKeyCallback(window, staticKeyCallback);
	glfwSetCharCallback(window, staticCharCallback);
	glfwSetCursorPosCallback(window, staticCursorPosCallback);
	glfwSetCursorEnterCallback(window, staticCursorEnterCallback);
	glfwSetMouseButtonCallback(window, staticMouseButtonCallback);
	glfwSetScrollCallback(window, staticScrollCallback);
	glfwSetDropCallback(window, staticDropCallback);
}

// static functions to rout glfw event callbacks through

void Window::staticWindowPosCallback(GLFWwindow *glfwWindow, int xpos, int ypos) {
	Window* self = static_cast<Window*>(
		glfwGetWindowUserPointer(glfwWindow)
	);

	self->windowPosCallback(xpos, ypos);
}

void Window::staticWindowSizeCallback(GLFWwindow *glfwWindow, int width, int height) {
	Window* self = static_cast<Window*>(
		glfwGetWindowUserPointer(glfwWindow)
	);

	self->windowSizeCallback(width, height);
}

void Window::staticWindowCloseCallback(GLFWwindow *glfwWindow) {
	Window* self = static_cast<Window*>(
		glfwGetWindowUserPointer(glfwWindow)
	);

	self->windowCloseCallback();
}

void Window::staticWindowRefreshCallback(GLFWwindow *glfwWindow) {
	Window* self = static_cast<Window*>(
		glfwGetWindowUserPointer(glfwWindow)
	);

	self->windowRefreshCallback();
}

void Window::staticWindowFocusCallback(GLFWwindow *glfwWindow, int focused) {
	Window* self = static_cast<Window*>(
		glfwGetWindowUserPointer(glfwWindow)
	);

	self->windowFocusCallback(focused);
}

void Window::staticWindowIconifyCallback(GLFWwindow *glfwWindow, int iconified) {
	Window* self = static_cast<Window*>(
		glfwGetWindowUserPointer(glfwWindow)
	);

	self->windowIconifyCallback(iconified);
}

void Window::staticWindowMaximizeCallback(GLFWwindow *glfwWindow, int maximized) {
	Window* self = static_cast<Window*>(
		glfwGetWindowUserPointer(glfwWindow)
	);

	self->windowMaximizeCallback(maximized);
}

void Window::staticFramebufferSizeCallback(GLFWwindow *glfwWindow, int width, int height) {
	Window* self = static_cast<Window*>(
		glfwGetWindowUserPointer(glfwWindow)
	);

	self->framebufferSizeCallback(width, height);
}

void Window::staticWindowContentScaleCallback(GLFWwindow *glfwWindow, float xscale, float yscale) {
	Window* self = static_cast<Window*>(
		glfwGetWindowUserPointer(glfwWindow)
	);

	self->windowContentScaleCallback(xscale, yscale);
}

void Window::staticKeyCallback(GLFWwindow *glfwWindow, int key, int scancode, int action, int mods) {
	Window* self = static_cast<Window*>(
		glfwGetWindowUserPointer(glfwWindow)
	);

	self->keyCallback(key, scancode, action, mods);
}

void Window::staticCharCallback(GLFWwindow *glfwWindow, unsigned int codepoint) {
	Window* self = static_cast<Window*>(
		glfwGetWindowUserPointer(glfwWindow)
	);

	self->charCallback(codepoint);
}

void Window::staticCursorPosCallback(GLFWwindow *glfwWindow, double xpos, double ypos) {
	Window* self = static_cast<Window*>(
		glfwGetWindowUserPointer(glfwWindow)
	);

	self->cursorPosCallback(xpos, ypos);
}

void Window::staticCursorEnterCallback(GLFWwindow *glfwWindow, int entered) {
	Window* self = static_cast<Window*>(
		glfwGetWindowUserPointer(glfwWindow)
	);

	self->cursorEnterCallback(entered);
}

void Window::staticMouseButtonCallback(GLFWwindow *glfwWindow, int button, int action, int mods) {
	Window* self = static_cast<Window*>(
		glfwGetWindowUserPointer(glfwWindow)
	);

	self->mouseButtonCallback(button,  action, mods);
}

void Window::staticScrollCallback(GLFWwindow *glfwWindow, double xoffset, double yoffset) {
	Window* self = static_cast<Window*>(
		glfwGetWindowUserPointer(glfwWindow)
	);

	self->scrollCallback(xoffset, yoffset);
}

void Window::staticDropCallback(GLFWwindow *glfwWindow, int path_count, const char **paths) {
	Window* self = static_cast<Window*>(
		glfwGetWindowUserPointer(glfwWindow)
	);

	self->dropCallback(path_count, paths);
}

// internal event functions

void Window::windowPosCallback(int xpos, int ypos) {
	if (customWindowPosCallback)
		customWindowPosCallback(window, xpos, ypos);
}

void Window::windowSizeCallback(int width, int height) {
	if (customWindowSizeCallback)
		customWindowSizeCallback(window, width, height);
}

void Window::windowCloseCallback() {
	if (customWindowCloseCallback)
		customWindowCloseCallback(window);
}

void Window::windowRefreshCallback() {
	if (customWindowRefreshCallback)
		customWindowRefreshCallback(window);
}

void Window::windowFocusCallback(int focused) {
	if (customWindowFocusCallback)
		customWindowFocusCallback(window, focused);
}

void Window::windowIconifyCallback(int iconified) {
	if (customWindowIconifyCallback)
		customWindowIconifyCallback(window, iconified);
}

void Window::windowMaximizeCallback(int maximized) {
	if (customWindowMaximizeCallback)
		customWindowMaximizeCallback(window, maximized);
}

void Window::framebufferSizeCallback(int width, int height) {
	this->width = width;
	this->height = height;

	glViewport(0, 0, width, height);

	if (customFramebufferSizeCallback)
		customFramebufferSizeCallback(window, width, height);
}

void Window::windowContentScaleCallback(float xscale, float yscale) {
	if (customWindowContentScaleCallback)
		customWindowContentScaleCallback(window, xscale, yscale);
}

void Window::keyCallback(int key, int scancode, int action, int mods) {
	if (customKeyCallback)
		customKeyCallback(window, key, scancode, action, mods);
}

void Window::charCallback(unsigned int codepoint) {
	if (customCharCallback)
		customCharCallback(window, codepoint);
}

void Window::cursorPosCallback(double xpos, double ypos) {
	if (customCursorPosCallback)
		customCursorPosCallback(window, xpos, ypos);
}

void Window::cursorEnterCallback(int entered) {
	if (customCursorEnterCallback)
		customCursorEnterCallback(window, entered);
}

void Window::mouseButtonCallback(int button, int action, int mods) {
	if (customMouseButtonCallback)
		customMouseButtonCallback(window, button, action, mods);
}

void Window::scrollCallback(double xoffset, double yoffset) {
	if (customScrollCallback)
		customScrollCallback(window, xoffset, yoffset);
}

void Window::dropCallback(int path_count, const char **paths) {
	if (customDropCallback)
		customDropCallback(window, path_count, paths);
}

// custom event setting function

void Window::setWindowPosCallback(GLFWwindowposfun callback) {
	customWindowPosCallback = callback;
}

void Window::setWindowSizeCallback(GLFWwindowsizefun callback) {
	customWindowSizeCallback = callback;
}

void Window::setWindowCloseCallback(GLFWwindowclosefun callback) {
	customWindowCloseCallback = callback;
}

void Window::setWindowRefreshCallback(GLFWwindowrefreshfun callback) {
	customWindowRefreshCallback = callback;
}

void Window::setWindowFocusCallback(GLFWwindowfocusfun callback) {
	customWindowFocusCallback = callback;
}

void Window::setWindowIconifyCallback(GLFWwindowiconifyfun callback) {
	customWindowIconifyCallback = callback;
}

void Window::setWindowMaximizeCallback(GLFWwindowmaximizefun callback) {
	customWindowMaximizeCallback = callback;
}

void Window::setFramebufferSizeCallback(GLFWframebuffersizefun callback) {
	customFramebufferSizeCallback = callback;
}

void Window::setWindowContentScaleCallback(GLFWwindowcontentscalefun callback) {
	customWindowContentScaleCallback = callback;
}

void Window::setKeyCallback(GLFWkeyfun callback) {
	customKeyCallback = callback;
}

void Window::setCharCallback(GLFWcharfun callback) {
	customCharCallback = callback;
}

void Window::setCursorPosCallback(GLFWcursorposfun callback) {
	customCursorPosCallback = callback;
}

void Window::setCursorEnterCallback(GLFWcursorenterfun callback) {
	customCursorEnterCallback = callback;
}

void Window::setMouseButtonCallback(GLFWmousebuttonfun callback) {
	customMouseButtonCallback = callback;
}

void Window::setScrollCallback(GLFWscrollfun callback) {
	customScrollCallback = callback;
}

void Window::setDropCallback(GLFWdropfun callback) {
	customDropCallback = callback;
}
