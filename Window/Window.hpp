#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../glad/glad.h"
#include <GLFW/glfw3.h>

class Window {
	public:
		Window(int width, int height, bool fullscreen = false);
		
		int width;
		int height;
		bool fullscreen;
		
		void loop();
		void clean();

	private:
		GLFWwindow* window;
		bool initOpenGL();
};

#endif
