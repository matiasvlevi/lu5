#include "../lu5_window.h"
#include "../lu5_state.h"


#include "../bindings/window.h"

#include "./stb/stb_image.h"
#include "../static/lu5_icon.h"

#include <lauxlib.h>

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

static void framebuffer_size_callback(lu5_window* window, int width, int height)
{
	// Get window resized callback
	lua_getglobal(lu5.L, LU5_WINDOW_RESIZED);
	if (lua_isfunction(lu5.L, -1)) 
	{
		// Pass arguments
		lua_pushnumber(lu5.L, width);
		lua_pushnumber(lu5.L, height);

		// Call
		if (lua_pcall(lu5.L, 2, 0, 0) != LUA_OK) {
			luaL_error(lu5.L, lua_tostring(lu5.L, -1));
		}
	}
}

static void lu5_init_2D(int width, int height) 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
	
	glViewport(0, 0, width, height);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Enable alpha blend
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH); 

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST); 
	glEnable(GL_POLYGON_SMOOTH);

	glDisable(GL_DEPTH_TEST); 
	glEnable(GL_ALPHA_TEST);
}

static void lu5_init_3D(int width, int height) 
{
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	

	gluPerspective(-45, (double)width / height, 0.1, 30000.0);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_SMOOTH); 

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST); 
	glEnable(GL_POLYGON_SMOOTH);
}

lu5_window *lu5_create_lu5_window(
	lua_State *L,
	int width,
	int height,
	const char *window_title,
	int depth_mode)
{
	// If window exists, use it.
	if (lu5.window != NULL) {
		return lu5.window;
	}

	lu5_window* window = (lu5_window*)glfwCreateWindow(
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

	// Set window icon
	GLFWimage images[1];
	images[0].pixels = stbi_load_from_memory(
		lu5_icon_png, sizeof(lu5_icon_png), 
		&images[0].width,
		&images[0].height,
		0, 4);
	glfwSetWindowIcon(window, 1, images);
	stbi_image_free(images[0].pixels);

	if (depth_mode == LU5_GL2D) {
		// Configure for 2D
		lu5_init_2D(width, height);
		lu5.depth_mode = LU5_GL2D;
	} else if (depth_mode == LU5_GL3D) {
		lu5_init_3D(width, height);
		lu5.depth_mode = LU5_GL3D;
	} else {
		luaL_error(L, "Unknown window rendering mode");
		return 0;
	}

	// Expose window width & height to user
	lu5_update_window_size(&lu5, width, height);

	return window;
}