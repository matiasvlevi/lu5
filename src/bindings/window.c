
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

int createWindow(lua_State *L) 
{
	int argc = lua_gettop(L);
	if (argc != 2 && argc != 3) {
		luaL_error(L, "Expected 2 or 3 arguments, width, height and mode");
		return 0;
	}

	lua_Integer width = lu5_assert_integer(L, 1, "createWindow");
	lua_Integer height = lu5_assert_integer(L, 2, "createWindow");

	lua_Integer depth_mode = LU5_GL2D;
	if (lua_isinteger(L, 3)) {
		depth_mode = lua_tointeger(L, 3);
	}

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

	// Create window
	GLFWwindow* window = lu5_create_glfw_window(L,
		width, height, 
		window_title,
		depth_mode
	); 

	// Window title was copied in the window
	free(window_title);

	if (window == NULL) {
		luaL_error(L, "Something went wrong when creating the window");
		return 0;
	};

	// Expose window width & height to user
	lua_pushnumber(L, width);
	lua_setglobal(L, LU5_WIDTH);

	lua_pushnumber(L, height);
	lua_setglobal(L, LU5_HEIGHT);

	// Set glfw window in global scope 
	lua_pushlightuserdata(L, window);
	lua_setglobal(L, "window");

	lu5.width = width;
	lu5.height = height;
	
	lu5_load_default_font(&lu5);

	return 0;
}

int frameRate(lua_State *L) 
{
	if (lua_gettop(L) > 0) 
	{
		lu5.env.target_framerate = lu5_assert_number(L, 1, "frameRate");
		return 0;
	} 
	else 
	{
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

int noLoop(lua_State *L)
{
	lu5.loop = false;

	return 0;
}

int loop(lua_State *L)
{
	lu5.loop = true;

	return 0;
}