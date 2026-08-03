#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../external/glad/glad.h"
#include <GLFW/glfw3.h>

class Window {
public:
	Window(int width, int height, bool fullscreen = false);

	int width;
	int height;
	bool fullscreen;

	// Window events
	void setWindowPosCallback(GLFWwindowposfun callback);                   // Window moved
	void setWindowSizeCallback(GLFWwindowsizefun callback);                 // Window resized
	void setWindowCloseCallback(GLFWwindowclosefun callback);               // Window close requested
	void setWindowRefreshCallback(GLFWwindowrefreshfun callback);           // Window needs redraw
	void setWindowFocusCallback(GLFWwindowfocusfun callback);               // Window gained/lost focus
	void setWindowIconifyCallback(GLFWwindowiconifyfun callback);           // Window minimized/restored
	void setWindowMaximizeCallback(GLFWwindowmaximizefun callback);         // Window maximized/restored
	void setFramebufferSizeCallback(GLFWframebuffersizefun callback);       // Framebuffer resized
	void setWindowContentScaleCallback(GLFWwindowcontentscalefun callback); // DPI/content scale changed

	// Keyboard events
	void setKeyCallback(GLFWkeyfun callback);                               // Key pressed/released/repeated
	void setCharCallback(GLFWcharfun callback);                             // Unicode character input

	// Mouse events
	void setCursorPosCallback(GLFWcursorposfun callback);                   // Mouse moved
	void setCursorEnterCallback(GLFWcursorenterfun callback);               // Mouse entered/left window
	void setMouseButtonCallback(GLFWmousebuttonfun callback);               // Mouse button pressed/released
	void setScrollCallback(GLFWscrollfun callback);                         // Mouse wheel scrolled

	// File events
	void setDropCallback(GLFWdropfun callback);                             // Files dropped onto window

	void loop();
	void clean();

private:
	GLFWwindow *window;
	bool initOpenGL();
};

#endif
