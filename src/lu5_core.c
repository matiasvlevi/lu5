#include "lu5_core.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "lu5_bindings.h"
#include "lu5_event_callbacks.h"
#include "lu5_color.h"
#include "lu5_image.h"
#include "lu5_font.h"
#include "lu5_obj.h"
#include "lu5_types.h"
#include "geometry/lu5_geometry.h"
#include "bindings/mouse.h"

static int lu5_run_setup(lu5_State *l5) 
{
	// Get the setup function, if found, run it
	lua_getglobal(l5->L, "setup");
	if (lua_isfunction(l5->L, -1)) 
	{
		LU5_RUN_LOG("setup");

		// Run Setup
		lua_getglobal(l5->L, "setup"); 
		if (lua_pcall(l5->L, 0, 0, 0) != LUA_OK) {
			return 1;
		}
	}
	return 0;
}

static void lu5_run_draw(lu5_State *l5, GLFWwindow *window) 
{
	if (l5->loop) 
	{
		lua_getglobal(l5->L, "draw");

		if (lua_pcall(l5->L, 0, 0, 0) != LUA_OK) 
		{
			LU5_ERROR(lua_tostring(l5->L, -1));
			// EXIT
			glfwSetWindowShouldClose(window, 1);
		} 
		else if (l5->debug)
		{
			if (l5->depth_mode == LU5_GL3D) lu5_render_debug();
			// else lu5_render_debug_2D(); // TODO:
		}

		glfwSwapBuffers(window);
	}

	// Still allow polling events for Restarts
	glfwPollEvents();
}

void lu5_init(lu5_State *l5)
{
	lu5_init_state(l5);

	l5->L = luaL_newstate();
	luaL_openlibs(l5->L);

	lu5_init_freetype(l5);

	// When log level is set to DEBUG (gt than 5)
	// lu5 will log integer and number types at startup
	lu5_log_types();
}

int lu5_run_sketch(lu5_State *l5, const char *filename)
{
	// Start lu5 & lua
	lu5_init(l5);

	// Register functions & constants
	lu5_register_symbols(l5->L);
	lu5_register_colors(l5->L);

	// Add `sketch` as a string variable holding the filename
	lua_pushstring(l5->L, filename);
	lua_setglobal(l5->L, "sketch");
	
	// Print Running log
	LU5_RUN_LOG(filename);

	// Run the file
	if (luaL_dofile(l5->L, filename) != LUA_OK) {
		LU5_ERROR(lua_tostring(l5->L, -1));
		return 0;
	}

	// Get the setup function, if found, run it
	// if None found, ignore
	if (lu5_run_setup(l5)) {
		// Setup threw an error
		LU5_ERROR(lua_tostring(l5->L, -1));
		return 0; 
	}

	// Get the draw function, if not found, exit
	lua_getglobal(l5->L, "draw");
	if (!lua_isfunction(l5->L, -1)) {
		return 0;
	}

	// Check if window was created from lua,
	// not found, exit
	lua_getglobal(l5->L, "window");
	if (!lua_isuserdata(l5->L, -1)) {
		LU5_WARN(LU5_NO_WINDOW);
		return 0;
	}

	// Window global was defined
	// not found, exit
	GLFWwindow *window = (GLFWwindow*)lua_touserdata(l5->L, -1);
	l5->window = window;

	if (window == NULL) {
		LU5_ERROR(LU5_INVALID_WINDOW);
		l5->env.restart = false;
		return 0;
	};
	
	// Register Event Callbacks
	lu5_register_event_callbacks(window);

	// Set window mouse values before calling draw
	double width, height;
	glfwGetCursorPos(window, &width, &height);

	LUA_ADD_NUMBER_GLOBAL_BY_NAME(l5->L, LU5_PMOUSE_X, width);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(l5->L, LU5_PMOUSE_Y, height);

	LUA_ADD_NUMBER_GLOBAL_BY_NAME(l5->L, LU5_MOUSE_X, width);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(l5->L, LU5_MOUSE_Y, height);

	LU5_RUN_LOG("draw");

	l5->env.last_time = glfwGetTime();
	l5->env.restart = false;

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window) && !l5->env.restart)
	{
		// Update environement values
		l5->env.now_time = glfwGetTime();
		l5->env.delta_time = (l5->env.now_time - l5->env.last_time);

		lu5_update_dynamic_variables(l5, window);

		// If no target framerate, draw
		if (l5->env.target_framerate == -1) 
		{
			lu5_run_draw(l5, window);
		} 
		else 
		{
			// Check if should render
			if((l5->env.now_time - l5->env.last_frame_time) >= (1.0 / l5->env.target_framerate)) 
			{
				// TODO: handle events in `./src/lu5_event_callbacks.c` the same way
				lu5_run_draw(l5, window);

				// Record for framerate
				l5->env.last_frame_time = l5->env.now_time;
			}
		}

		// Record for delta_time
		l5->env.last_time = l5->env.now_time;
	}

	lu5_close(l5);

	return 0;
}

void lu5_close(lu5_State *l5) 
{
	lu5_close_images(l5);

	lu5_close_models(l5);

	lu5_close_fonts(l5);

	lu5_style_clear(l5);

	if (l5->orbit != NULL) {
		free(l5->orbit);
		l5->orbit = NULL;
	}

	if (l5->ft != NULL) {
		FT_Done_FreeType(l5->ft);
		l5->ft = NULL;
	}

	if (l5->L != NULL) {
		lua_gc(l5->L, LUA_GCCOLLECT, 0);
		lua_close(l5->L);
		l5->L = NULL;
	}
}
