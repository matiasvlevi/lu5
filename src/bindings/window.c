
#include <GL/glu.h>
#include "window.h"

#include "../lu5_bindings.h"
#include "../lu5_state.h"
#include "../lu5_font.h"
#include "../lu5_types.h"

#include <stdio.h>
#include <stdlib.h>
#include <lauxlib.h>

#include <math.h>
#include "../lu5_window.h"



static void lu5_setup_2D(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
	
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

static void lu5_setup_3D(GLFWwindow* window) {
	glEnable(GL_DEPTH_TEST);
	
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
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

int createWindow(lua_State *L) 
{
	int argc = lua_gettop(L);
	if (argc != 2 && argc != 3) {
		luaL_error(L, "Expected 2 or 3 arguments, width, height and mode");
		return 0;
	}

	lua_Integer screenWidth = lu5_assert_integer(L, 1, "createWindow");
	lua_Integer screenHeight = lu5_assert_integer(L, 2, "createWindow");

	lua_Integer depth_mode = LU5_GL2D;
	if (lua_isinteger(L, 3)) {
		depth_mode = lua_tointeger(L, 3);
	}

	// Expose window width & height to user
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, LU5_WIDTH, screenWidth);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, LU5_HEIGHT, screenHeight); 

	//
	lua_getglobal(L, "sketch");
	const char *sketch_path = luaL_checkstring(L, -1);
	if (sketch_path == NULL) {
		LU5_WARN("The 'sketch' file path was altered, the window cannot find a name");
	};

	// Add prefix to window title
	int len = luaL_len(L, -1);
	char* window_title = malloc(len + 10);

	sprintf(window_title, "[lu5]: %s", sketch_path);

	//
	GLFWwindow* window = lu5_create_glfw_window(L,
		screenWidth, screenHeight, 
		window_title
	); 

	// Window title was copied in the window
	free(window_title);

	if (window == NULL) {
		luaL_error(L, "Something went wrong when creating the window");
		return 0;
	};

	// Set glfw window in global scope 
	lua_pushlightuserdata(L, window);
	lua_setglobal(L, "window");



	if (depth_mode == LU5_GL2D) {
		// Configure for 2D
		lu5_setup_2D(screenWidth, screenHeight);
		lu5.depth_mode = LU5_GL2D;
	} else if (depth_mode == LU5_GL3D) {
		lu5_setup_3D(window);
		lu5.depth_mode = LU5_GL3D;
	} else {
		luaL_error(L, "Unknown window rendering mode");
		return 0;
	}

	
	// Load default font statically
	int err = lu5_load_font(&lu5, &(lu5.font_default), NULL);
	if (err != FT_Err_Ok) {
		luaL_error(L, "Error loading default font, code: %i", err);
		return 0;
	}

	// Set the current as the default font
	lu5.style.font_current = lu5.font_default;

	return 0;
}

int frameRate(lua_State *L) 
{
	if (lua_gettop(L) > 0) {
		lu5.env.target_framerate = lu5_assert_number(L, 1, "frameRate");
		return 0;
	} else {
		// Return the current framerate

		if (lu5.env.target_framerate == -1) 
			// For free frame rates
			lua_pushnumber(L, roundf(1000.0 / (lu5.env.delta_time))/1000.0);
		else
			// For fixed frame rates
			lua_pushnumber(L, roundf(1000.0 / (lu5.env.now_time - lu5.env.last_frame_time))/1000.0);

		return 1;
	}
}
