#pragma once

#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Shader.hpp>
#include <Geometry/Mesh.hpp>
#include <Geometry/Model.hpp>
#include <Camera.hpp>

struct MeshEntry {
	std::string id;
	Mesh mesh;
};

struct ModelEntry {
	std::string id;
	Model model;
};

class Window {
public:
	Window(int width = 854, int height = 480, bool fullscreen = false);
	~Window();

	GLFWwindow *getWindow();

	int getWidth() { return width; }
	int getHeight() { return height; }
	bool getFullscreen() { return fullscreen; }

	bool hasCamera(const std::string& id) const {
		return cameras.find(id) != cameras.end();
	}

	bool hasShader(const std::string& id) const {
		return shaders.find(id) != shaders.end();
	}

	void addCamera(Camera camera, std::string id) {
		cameras.insert_or_assign(std::move(id), std::move(camera));
	}

	void addShader(std::string id, const std::string& vertexPath, const std::string& fragmentPath) {
		shaders.try_emplace(
			std::move(id),
			vertexPath,
			fragmentPath
		);
	}

	void addMesh(Mesh mesh, std::string shaderID, std::string camID, std::string meshID) {
		if (!hasShader(shaderID)) {
			throw std::runtime_error("addMesh: no shader registered with id \"" + shaderID + "\"");
		}

		if (!hasCamera(camID)) {
			throw std::runtime_error("addMesh: no camera registered with id \"" + camID + "\"");
		}

		MeshEntry meshE = {
			std::move(meshID),
			std::move(mesh),
		};

		meshes[shaderID][camID].push_back(std::move(meshE));
	}

	void addModel(Model model, std::string shaderID, std::string camID, std::string modelID) {
		if (!hasShader(shaderID)) {
			throw std::runtime_error("addModel: no shader registered with id \"" + shaderID + "\"");
		}

		if (!hasCamera(camID)) {
			throw std::runtime_error("addModel: no camera registered with id \"" + camID + "\"");
		}

		ModelEntry modelE = {
			std::move(modelID),
			std::move(model),
		};

		models[shaderID][camID].push_back(std::move(modelE));
	}

	// Window events
	void setWindowPosCallback(GLFWwindowposfun callback);					// Window moved
	void setWindowSizeCallback(GLFWwindowsizefun callback);					// Window resized
	void setWindowCloseCallback(GLFWwindowclosefun callback);				// Window close requested
	void setWindowRefreshCallback(GLFWwindowrefreshfun callback);			// Window needs redraw
	void setWindowFocusCallback(GLFWwindowfocusfun callback);				// Window gained/lost focus
	void setWindowIconifyCallback(GLFWwindowiconifyfun callback);			// Window minimized/restored
	void setWindowMaximizeCallback(GLFWwindowmaximizefun callback);			// Window maximized/restored
	void setFramebufferSizeCallback(GLFWframebuffersizefun callback);		// Framebuffer resized
	void setWindowContentScaleCallback(GLFWwindowcontentscalefun callback);	// DPI/content scale changed

	// Keyboard events
	void setKeyCallback(GLFWkeyfun callback);								// Key pressed/released/repeated
	void setCharCallback(GLFWcharfun callback);								// Unicode character input

	// Mouse events
	void setCursorPosCallback(GLFWcursorposfun callback);					// Mouse moved
	void setCursorEnterCallback(GLFWcursorenterfun callback);				// Mouse entered/left window
	void setMouseButtonCallback(GLFWmousebuttonfun callback);				// Mouse button pressed/released
	void setScrollCallback(GLFWscrollfun callback);							// Mouse wheel scrolled

	// File events
	void setDropCallback(GLFWdropfun callback);								// Files dropped onto window

	void loop();

private:
	GLFWwindow *window;

	int width{};
	int height{};
	bool fullscreen{};

	std::unordered_map<std::string, Camera> cameras;
	std::unordered_map<std::string, Shader> shaders;

	// map<shaderID, map<CamID, vector<{objectID, object}>>>
	std::unordered_map<std::string, std::unordered_map<std::string, std::vector<MeshEntry>>> meshes;
	std::unordered_map<std::string, std::unordered_map<std::string, std::vector<ModelEntry>>> models;

	bool initOpenGL(int width, int height);
	bool checkError(const char* where);

	void setInternalCallbacks();

	// static functions to rout glfw event callbacks through
	static void staticWindowPosCallback(GLFWwindow *glfwWindow, int xpos, int ypos);
	static void staticWindowSizeCallback(GLFWwindow *glfwWindow, int width, int height);
	static void staticWindowCloseCallback(GLFWwindow *glfwWindow);
	static void staticWindowRefreshCallback(GLFWwindow *glfwWindow);
	static void staticWindowFocusCallback(GLFWwindow *glfwWindow, int focused);
	static void staticWindowIconifyCallback(GLFWwindow *glfwWindow, int iconified);
	static void staticWindowMaximizeCallback(GLFWwindow *glfwWindow, int maximized);
	static void staticFramebufferSizeCallback(GLFWwindow *glfwWindow, int width, int height);
	static void staticWindowContentScaleCallback(GLFWwindow *glfwWindow, float xscale, float yscale);
	static void staticKeyCallback(GLFWwindow *glfwWindow, int key, int scancode, int action, int mods);
	static void staticCharCallback(GLFWwindow *glfwWindow, unsigned int codepoint);
	static void staticCursorPosCallback(GLFWwindow *glfwWindow, double xpos, double ypos);
	static void staticCursorEnterCallback(GLFWwindow *glfwWindow, int entered);
	static void staticMouseButtonCallback(GLFWwindow *glfwWindow, int button, int action, int mods);
	static void staticScrollCallback(GLFWwindow *glfwWindow, double xoffset, double yoffset);
	static void staticDropCallback(GLFWwindow *glfwWindow, int path_count, const char **paths);

	// internal event functions
	void windowPosCallback(int xpos, int ypos);
	void windowSizeCallback(int width, int height);
	void windowCloseCallback();
	void windowRefreshCallback();
	void windowFocusCallback(int focused);
	void windowIconifyCallback(int iconified);
	void windowMaximizeCallback(int maximized);
	void framebufferSizeCallback(int width, int height);
	void windowContentScaleCallback(float xscale, float yscale);
	void keyCallback(int key, int scancode, int action, int mods);
	void charCallback(unsigned int codepoint);
	void cursorPosCallback(double xpos, double ypos);
	void cursorEnterCallback(int entered);
	void mouseButtonCallback(int button, int action, int mods);
	void scrollCallback(double xoffset, double yoffset);
	void dropCallback(int path_count, const char **paths);

	// custom event functions
	GLFWwindowposfun customWindowPosCallback = nullptr;
	GLFWwindowsizefun customWindowSizeCallback = nullptr;
	GLFWwindowclosefun customWindowCloseCallback = nullptr;
	GLFWwindowrefreshfun customWindowRefreshCallback = nullptr;
	GLFWwindowfocusfun customWindowFocusCallback = nullptr;
	GLFWwindowiconifyfun customWindowIconifyCallback = nullptr;
	GLFWwindowmaximizefun customWindowMaximizeCallback = nullptr;
	GLFWframebuffersizefun customFramebufferSizeCallback = nullptr;
	GLFWwindowcontentscalefun customWindowContentScaleCallback = nullptr;
	GLFWkeyfun customKeyCallback = nullptr;
	GLFWcharfun customCharCallback = nullptr;
	GLFWcursorposfun customCursorPosCallback = nullptr;
	GLFWcursorenterfun customCursorEnterCallback = nullptr;
	GLFWmousebuttonfun customMouseButtonCallback = nullptr;
	GLFWscrollfun customScrollCallback = nullptr;
	GLFWdropfun customDropCallback = nullptr;
};
