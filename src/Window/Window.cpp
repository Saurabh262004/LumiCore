#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <random>

#include <Util.hpp>
#include <Geometry/Vec.hpp>
#include <Geometry/Mesh.hpp>
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
	Vertex cube[] = {
		// Front face — normal (0,0,1)
		{{-0.5f,-0.5f, 0.5f},{0,0,1}}, {{0.5f,-0.5f, 0.5f},{0,0,1}}, {{0.5f, 0.5f, 0.5f},{0,0,1}},
		{{0.5f, 0.5f, 0.5f},{0,0,1}}, {{-0.5f, 0.5f, 0.5f},{0,0,1}}, {{-0.5f,-0.5f, 0.5f},{0,0,1}},
		// Back face — normal (0,0,-1)
		{{-0.5f,-0.5f,-0.5f},{0,0,-1}}, {{-0.5f, 0.5f,-0.5f},{0,0,-1}}, {{0.5f, 0.5f,-0.5f},{0,0,-1}},
		{{0.5f, 0.5f,-0.5f},{0,0,-1}}, {{0.5f,-0.5f,-0.5f},{0,0,-1}}, {{-0.5f,-0.5f,-0.5f},{0,0,-1}},
		// Left face — normal (-1,0,0)
		{{-0.5f, 0.5f, 0.5f},{-1,0,0}}, {{-0.5f, 0.5f,-0.5f},{-1,0,0}}, {{-0.5f,-0.5f,-0.5f},{-1,0,0}},
		{{-0.5f,-0.5f,-0.5f},{-1,0,0}}, {{-0.5f,-0.5f, 0.5f},{-1,0,0}}, {{-0.5f, 0.5f, 0.5f},{-1,0,0}},
		// Right face — normal (1,0,0)
		{{0.5f, 0.5f, 0.5f},{1,0,0}}, {{0.5f,-0.5f,-0.5f},{1,0,0}}, {{0.5f, 0.5f,-0.5f},{1,0,0}},
		{{0.5f,-0.5f,-0.5f},{1,0,0}}, {{0.5f, 0.5f, 0.5f},{1,0,0}}, {{0.5f,-0.5f, 0.5f},{1,0,0}},
		// Top face — normal (0,1,0)
		{{-0.5f, 0.5f,-0.5f},{0,1,0}}, {{-0.5f, 0.5f, 0.5f},{0,1,0}}, {{0.5f, 0.5f, 0.5f},{0,1,0}},
		{{0.5f, 0.5f, 0.5f},{0,1,0}}, {{0.5f, 0.5f,-0.5f},{0,1,0}}, {{-0.5f, 0.5f,-0.5f},{0,1,0}},
		// Bottom face — normal (0,-1,0)
		{{-0.5f,-0.5f,-0.5f},{0,-1,0}}, {{0.5f,-0.5f,-0.5f},{0,-1,0}}, {{0.5f,-0.5f, 0.5f},{0,-1,0}},
		{{0.5f,-0.5f, 0.5f},{0,-1,0}}, {{-0.5f,-0.5f, 0.5f},{0,-1,0}}, {{-0.5f,-0.5f,-0.5f},{0,-1,0}},
	};

	VertexLayout vertexLayout {
		sizeof(Vertex),
		{
			{ 0, 3, offsetof(Vertex, position) },
			{ 6, 3, offsetof(Vertex, normal) }
		}
	};

	Mesh mesh(cube, std::size(cube), vertexLayout);

	std::size_t count = 1000;

	std::vector<InstanceData> instances;
	instances.reserve(count);

	std::vector<float> xs       = Util::randFV(-1.0f, 1.0f, count);
	std::vector<float> ys       = Util::randFV(-1.0f, 1.0f, count);
	std::vector<float> zs       = Util::randFV(-1.0f, 1.0f, count);
	std::vector<float> rotXs    = Util::randFV(0.0f, 6.2831853f, count);
	std::vector<float> rotYs    = Util::randFV(0.0f, 6.2831853f, count);
	std::vector<float> rotZs    = Util::randFV(0.0f, 6.2831853f, count);
	std::vector<float> reds     = Util::randFV(0.0f, 1.0f, count);
	std::vector<float> greens   = Util::randFV(0.0f, 1.0f, count);
	std::vector<float> blues    = Util::randFV(0.0f, 1.0f, count);
	std::vector<float> scaleXs  = Util::randFV(0.002f, 0.05f, count);
	std::vector<float> scaleYs  = Util::randFV(0.002f, 0.05f, count);
	std::vector<float> scaleZs  = Util::randFV(0.002f, 0.05f, count);

	for (std::size_t i = 0; i < count; ++i) {
		Mat4 translated = Mat4::translate(Vec3{xs[i], ys[i], zs[i]});
		//Mat4 translated = Mat4::identity();

		Mat4 rotated = Mat4::rotateX(rotXs[i]) * Mat4::rotateY(rotYs[i]) * Mat4::rotateZ(rotZs[i]);
		//Mat4 rotated = Mat4::identity();

		Mat4 scaled = Mat4::scale(Vec3{scaleXs[i], scaleYs[i], scaleZs[i]});
		//Mat4 scaled = Mat4::identity();

		Mat4 model = translated * rotated * scaled;

		Vec3 color =  { reds[i], greens[i], blues[i] };

		instances.push_back(InstanceData{ model, color });
	}

	mesh.setInstanceData(instances.data(), instances.size());

	Shader shader("shaders/shader.vert", "shaders/shader.frag");

	// Render Loop

	int frames = 0;

	double lastTime = glfwGetTime();

	float stopPoint = M_PI * 2;
	float step = 0.002;

	//camera.setPosition({0.0f, 0.0f, 3.0f});

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		frames++;
		double currentTime = glfwGetTime();

		if (currentTime - lastTime >= 1.0) {
			std::cout << "FPS: " << frames << '\n';

			frames = 0;
			lastTime += 1.0;
		}

		camera.updateViewProjection();

		shader.use();

		shader.setMat4("viewProjection", camera.getViewProjection());
		shader.setVec3("lightDir", Vec3{-0.5f, -1.0f, -0.3f});

		mesh.draw(instances.size());

		float roll = camera.getRoll();

		if (roll < stopPoint) {
			roll += step;

			camera.setRoll(roll);
			camera.setPitch(roll);
			camera.setYaw(roll);
		} else {
			camera.setRoll(stopPoint);
			camera.setPitch(stopPoint);
			camera.setYaw(stopPoint);
		}

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
