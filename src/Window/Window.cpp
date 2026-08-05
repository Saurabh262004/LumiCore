#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Util.hpp>
#include <Vertex.hpp>
#include <Mesh.hpp>
#include <Shader.hpp>
#include <Window.hpp>

Window::Window(int width, int height, bool fullscreen) {
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
		if (!initOpenGL(width, height)) {
			std::cerr << "Failed to initiate OpenGL\n";
		} else {
			glfwSetWindowUserPointer(window, this);
			setInternalCallbacks();
		}
	}
}

bool Window::initOpenGL(int width, int height) {
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
	//glFrontFace(GL_CW);

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
	Vertex square[] = {
		{{-0.25f,  0.25f, 0.0f}},
		{{-0.25f, -0.25f, 0.0f}},
		{{ 0.25f,  0.25f, 0.0f}},

		{{ 0.25f,  0.25f, 0.0f}},
		{{-0.25f, -0.25f, 0.0f}},
		{{ 0.25f, -0.25f, 0.0f}}
	};

	Mesh mesh(square, std::size(square));

	Shader shader("shaders/triangle.vert", "shaders/triangle.frag");

	// Render Loop

	int frames = 0;

	double lastTime = glfwGetTime();

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.15f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		frames++;
		double currentTime = glfwGetTime();

		if (currentTime - lastTime >= 1.0) {
			std::cout << "FPS: " << frames << '\n';

			frames = 0;
			lastTime += 1.0;
		}

		shader.use();

		mesh.draw();

		//GLenum err = glGetError();

		//if (err != GL_NO_ERROR) {
		//	std::cout << "OpenGL Error: " << err << '\n';
		//}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

Window::~Window() {
	std::cout << "Destroying GLFW\n";

	if (window) glfwDestroyWindow(window);
}

GLFWwindow *Window::getWindow() {
	return window;
}
