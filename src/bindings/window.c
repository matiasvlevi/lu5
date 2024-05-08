#include "window.h"

#include "../lu5_defs.h"
#include "../lu5_state.h"
#include "../lu5_font.h"

#include <stdio.h>
#include <stdlib.h>
#include <lauxlib.h>

static GLFWwindow *lu5_init_glfw(
	lua_State *L,
	int screenWidth,
	int screenHeight,
	const char *window_title)
{
	if (!glfwInit()) {
		luaL_error(L, "Failed to initialize GLFW\n");
		return NULL;
	}

	GLFWwindow* window = glfwCreateWindow(
		screenWidth, screenHeight,	 
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
	
	// Vsync
	glfwSwapInterval(1); 

	return window;
}

int createWindow(lua_State *L) {
	
	int screenWidth = lua_tointeger(L, 1);
	int screenHeight = lua_tointeger(L, 2);
	LUA_ADD_NUMBER_GLOBAL(L, "width", screenWidth);
	LUA_ADD_NUMBER_GLOBAL(L, "height", screenHeight); 

	lua_getglobal(L, "sketch");
	const char *sketch_path = luaL_checkstring(L, -1);
	if (sketch_path == NULL) return 1;

	int len = luaL_len(L, -1);

	// Add prefix to title
	char* window_title = malloc(len + 10);
	sprintf(window_title, "[lu5]: %s", sketch_path);

	GLFWwindow* window = lu5_init_glfw(L, 
		screenWidth, screenHeight, 
		window_title
	); 

	if (window == NULL)
	{
		return 0;
	}

	lua_pushlightuserdata(L, window);
	lua_setglobal(L, "window");

	// Configure for 2D
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, screenWidth, screenHeight, 0.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Line smoothing

	// Enable alpha blend
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH); 

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	#ifndef _WIN32
	glEnable(GL_MULTISAMPLE);  
	#endif
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST); 
	glEnable(GL_POLYGON_SMOOTH);

	glDisable( GL_DEPTH_TEST ); 
	glEnable( GL_ALPHA_TEST ); 

	// TODO: Have a built in static font instead of a TTF.
	// this macro comes from the compiler flags, 
	// please define your default font path if you wan to use `text` without using `loadFont`
	lu5_load_font(&lu5, LU5_DEFAULT_FONT_PATH, NULL);

	free(window_title);
	return 0;
}

int background(lua_State *L) {

	lu5_color color = lu5_args_to_color(L);

	glClearColor(
		((GLfloat)color.r)/255.0f, 
		((GLfloat)color.g)/255.0f, 
		((GLfloat)color.b)/255.0f, 
		((GLfloat)color.a)/255.0f
	);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	return 0;
}
