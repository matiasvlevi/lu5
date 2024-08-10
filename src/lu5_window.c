#include "lu5_window.h"

#include "bindings/window.h"

#include <lauxlib.h>

#include "stb/stb_image.h"
#include "static/lu5_icon.h"

#include "lu5_state.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

	lua_getglobal(lu5.L, LU5_WINDOW_RESIZED);
	if (lua_isfunction(lu5.L, -1)) {
		lua_pushnumber(lu5.L, width);
		lua_pushnumber(lu5.L, height);
		if (lua_pcall(lu5.L, 2, 0, 0) != LUA_OK) {
			luaL_error(lu5.L, lua_tostring(lu5.L, -1));
		}
	}

	//glViewport(0, 0, width, height);

}

GLFWwindow *lu5_create_glfw_window(
	lua_State *L,
	int width,
	int height,
	const char *window_title)
{
	// If window exists, use it.
	if (lu5.window != NULL) {
		return lu5.window;
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

	// No resize
	// glfwWindowHint(GLFW_RESIZABLE, false);

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Set necessary options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Set callback for when the window is resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Set window icon
	GLFWimage images[1];
	images[0].pixels = stbi_load_from_memory(
		lu5_icon_png, sizeof(lu5_icon_png), 
		&images[0].width,
		&images[0].height,
		0, 4);
	glfwSetWindowIcon(window, 1, images);
	stbi_image_free(images[0].pixels);

	return window;
}
