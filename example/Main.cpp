#include <iostream>

#include <lumi/Shader.hpp>
#include <lumi/Camera.hpp>
#include <lumi/Geometry/Model.hpp>
#include <lumi/Window.hpp>

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

//void fileDropCallback(GLFWwindow *window, int path_count, const char **paths) {
//	for (int i = 0; i < path_count; i++) {
//		std::cout << "Path " << i << ": " << paths[i] << std::endl;
//	}
//}

int main() {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW\n";
		return -1;
	}

	{
		Window window(1280, 720);

		window.addCamera("cam1");
		Camera* cam = window.getCamera("cam1");
		cam->setViewportResolution((float)1280, (float)720);
		cam->setPosition({-1.0f, 1.0f, 3.0f});

		window.addShader("shader1", "assets/shaders/shader.vert", "assets/shaders/shader.frag");
		Shader* shader1 = window.getShader("shader1");
		shader1->addVec3Uniform("lightDir", Vec3{-0.5f, -1.0f, -0.3f});

		window.addModel("shader1", "cam1", "model1", "assets/models/pyramid/obj");
		Model* model1 = window.getModel("shader1", "cam1", "model1");
		model1->addInstance({Mat4::translate({0.0f, 1.0f, 0.0f}), {0.7f, 0.0f, 0.5f}});
		model1->uploadInstances();

		window.addModel("shader1", "cam1", "model2", "assets/models/citlali/obj");
		Model* model2 = window.getModel("shader1", "cam1", "model2");
		model2->addInstance({Mat4::translate({-2.0f, 0.0f, 0.0f}), {0.0f, 1.0f, 1.0f}});
		model2->uploadInstances();

		//window.setFramebufferSizeCallback(resize);
		//window.setKeyCallback(keyCallback);
		//window.setCursorPosCallback(mouseMotionCallback);
		//window.setMouseButtonCallback(mouseButtonCallback);
		//window.setDropCallback(fileDropCallback);

		window.loop();
	}

	glfwTerminate();
}
