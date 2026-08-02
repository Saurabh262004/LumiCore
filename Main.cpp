#include <iostream>
#include "external/glad/glad.h"
#include <GLFW/glfw3.h>

#include "Window/Window.hpp"

int main()
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW\n";
		return -1;
	}

	Window window(800, 600);
	window.loop();
}
