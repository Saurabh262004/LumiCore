#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Util/Util.hpp"
#include "../Shader/Shader.hpp"
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
		if (!initOpenGL()) {
			std::cerr << "Failed to initiate OpenGL\n";
		}
	}
}

bool Window::initOpenGL() {
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD\n";
		return false;
	}

	std::cout << "GL VERSION: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GL VENDOR: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "GL RENDERER: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "GLSL VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glfwSwapInterval(0);

	glViewport(0, 0, width, height);

	return true;
}

void Window::checkError(const char* where) {
	GLenum err = glGetError();

	if (err != GL_NO_ERROR)
		std::cout << where << " : " << err << '\n';
}

void Window::loop() {
	// Triangle vertices
	float vertices[] = {
		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	// --------------------
	// Create VBO + VAO
	// --------------------

	GLuint VAO;
	GLuint VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind the VAO first
	glBindVertexArray(VAO);

	// Bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Upload vertex data
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(vertices),
		vertices,
		GL_STATIC_DRAW
	);

	// Tell OpenGL how the vertex data is laid out
	glVertexAttribPointer(
		0,                  // location
		3,                  // x y z
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(float),  // stride
		(void*)0            // offset
	);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	Shader shader("shaders/triangle.vert", "shaders/triangle.frag");

	// --------------------
	// Render Loop
	// --------------------

	//int frames = 0;

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.15f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();

		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		GLenum err = glGetError();

		if (err != GL_NO_ERROR)
		{
			std::cout << "OpenGL Error: " << err << '\n';
		}

		//frames++;
		//if (frames % 144 == 0) frames = 0;
		//std::cout << frames << std::endl;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// cleanup
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

Window::~Window() {
	std::cout << "Destroying GLFW\n";

	if (window) glfwDestroyWindow(window);
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

