#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW\n";
		return -1;
	}

	Window window(1280, 720);
	
	Camera cam;
	cam.setViewportResolution((float)1280, (float)720);
	cam.setPosition({0.0f, 1.0f, 3.0f});

	Model citlali("assets/models/citlali/obj");
	citlali.addNormalInstance();
	citlali.uploadInstances();

	window.addCamera(cam, "cam1");
	window.addModel(std::move(citlali), "cam1", "citlali");

	//window.setFramebufferSizeCallback(resize);
	//window.setKeyCallback(keyCallback);
	//window.setCursorPosCallback(mouseMotionCallback);
	//window.setMouseButtonCallback(mouseButtonCallback);

	window.loop();

	glfwTerminate();
}
