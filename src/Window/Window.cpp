#include <iostream>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <random>

#include <Util.hpp>
#include <Geometry/Vec.hpp>
#include <Geometry/Mesh.hpp>
#include <Geometry/Model.hpp>
#include <Shader.hpp>
#include <Window.hpp>

Window::Window(int width, int height, bool fullscreen) : width{width}, height{height}, fullscreen{fullscreen} {
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

	camera.setViewportResolution((float)width, (float)height);
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

	glfwSwapInterval(1);

	glViewport(0, 0, width, height);

	return true;
}

void Window::checkError(const char* where) {
	GLenum err = glGetError();

	if (err != GL_NO_ERROR)
		std::cout << where << " : " << err << '\n';
}

void Window::loop() {
	std::vector<InstanceData> instances = {
		{ Mat4::translate({0, 0, 0}), {1, 1, 1} },
	};

	Model pyramid("assets/Citlali/obj");

	pyramid.setInstanceData(instances.data(), instances.size());

	Shader shader("assets/shaders/shader.vert", "assets/shaders/shader.frag");

	camera.setPosition({0.0f, 1.0f, 3.0f});

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.updateViewProjection();

		shader.use();

		shader.setMat4("viewProjection", camera.getViewProjection());
		shader.setVec3("lightDir", Vec3{-0.5f, -1.0f, -0.3f});

		pyramid.draw(instances.size());

		GLenum err = glGetError();

		if (err != GL_NO_ERROR) {
			std::cout << "OpenGL Error: " << err << '\n';
		}

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
