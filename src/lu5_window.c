#include "lu5_window.h"
#include <lauxlib.h>

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWwindow *lu5_create_glfw_window(
	lua_State *L,
	int width,
	int height,
	const char *window_title)
{
	if (!glfwInit()) {
		luaL_error(L, "Failed to initialize GLFW\n");
		return NULL;
	}

	GLFWwindow* window = glfwCreateWindow(
		width, height,	 
		window_title, 
		NULL, NULL);

	if (window == NULL)
	{
		luaL_error(L, "Failed to create GLFW window\n");
		glfwTerminate();
		return NULL;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Set necessary options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Set callback for when the window is resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 

	return window;
}