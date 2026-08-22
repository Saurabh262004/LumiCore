#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Shader.hpp>
#include <Camera.hpp>
#include <Geometry/Model.hpp>
#include <Window.hpp>


//void resize(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//	std::cout << "Framebuffer resize width: " << width << ", height: " << height << '\n';
//}

//void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, true);
//	}
//}

//void mouseMotionCallback(GLFWwindow* window, double x, double y) {
//	std::cout << "cursor position x: " << x << ", y: " << y << '\n';
//}

//void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
//	if (action == GLFW_PRESS)  {
//		if (button == GLFW_MOUSE_BUTTON_LEFT) {
//			std::cout << "left\n";
//		} else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
//			std::cout << "right\n";
//		}
//	}
//}

int main() {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW\n";
		return -1;
	}

	{
		Window window(1280, 720);

		//Shader shader1("assets/shaders/shader.vert", "assets/shaders/shader.frag");

		Camera cam;
		cam.setViewportResolution((float)1280, (float)720);
		cam.setPosition({0.0f, 1.0f, 3.0f});

		Model model1("assets/models/pyramid/obj");
		model1.addNormalInstance();
		model1.uploadInstances();

		//window.addShader(std::move(shader1), "shader1");
		window.addShader("shader1", "assets/shaders/shader.vert", "assets/shaders/shader.frag");
		window.addCamera(std::move(cam), "cam1");
		window.addModel(std::move(model1), "shader1", "cam1", "model1");

		//window.setFramebufferSizeCallback(resize);
		//window.setKeyCallback(keyCallback);
		//window.setCursorPosCallback(mouseMotionCallback);
		//window.setMouseButtonCallback(mouseButtonCallback);

		window.loop();
	}

	glfwTerminate();
}
