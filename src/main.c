#include <stdio.h>
#include <stdlib.h>

#include <lauxlib.h>
#include <lualib.h>

#include "lu5_state.h"
#include "lu5_cli.h"
#include "lu5_cli_options.h"
#include "lu5_event_callbacks.h"
#include "lu5_logger.h"

#include "lu5_bindings.h"

#include "lu5_font.h"

static void lu5_draw(lu5_State *l5, GLFWwindow *window) 
{
	lua_getglobal(l5->L, "draw");
	if (lua_pcall(l5->L, 0, 0, 0) != LUA_OK) {
		LU5_ERROR(lua_tostring(l5->L, -1));
		// EXIT
		glfwSetWindowShouldClose(window, 1);
	}
	glfwSwapBuffers(window);
}

int main(int argc, char **argv) 
{

	char *filename;
	// return if option ran
	if (!handle_args(argc, argv, &filename)) 
		return 0;

	lu5_init_freetype(&lu5);
	
	// Start lua
	lu5.L = luaL_newstate();
	luaL_openlibs(lu5.L);

	// Add `sketch` as a variable holding the filename
	lua_pushstring(lu5.L, filename);
	lua_setglobal(lu5.L, "sketch");

	// Register functions & constants
	lu5_register_symbols(lu5.L);
	lu5_register_colors(lu5.L);

	// Print Running log
	LU5_RUN_LOG(filename);

	// Run the file
	if (luaL_dofile(lu5.L, filename) != LUA_OK) {
		LU5_ERROR(lua_tostring(lu5.L, -1));
		goto cleanup;
	}

	// Get the setup function, if found, run it
	lua_getglobal(lu5.L, "setup");
	if (lua_isfunction(lu5.L, -1)) {
		LU5_RUN_LOG("setup");

		// Run Setup
		lua_getglobal(lu5.L, "setup"); 
		if (lua_pcall(lu5.L, 0, 0, 0) != LUA_OK) {
			LU5_ERROR(lua_tostring(lu5.L, -1));
			goto cleanup;
		}
	} // else ignore;

	// Get the draw function, if not found, exit
	lua_getglobal(lu5.L, "draw");
	if (!lua_isfunction(lu5.L, -1)) {
		goto cleanup;
	}

	// Check if window was created from lua
	lua_getglobal(lu5.L, "window");
	if (!lua_isuserdata(lu5.L, -1)) {
		LU5_WARN(LU5_NO_WINDOW);
		goto cleanup;
	}

	// Window global was defined 
	// Get the GLFWwindow created from lua 
	GLFWwindow* window = (GLFWwindow*)lua_touserdata(lu5.L, -1);  
	if (!window) {
		LU5_ERROR(LU5_INVALID_WINDOW);
		goto cleanup;
	}

	// Register Event Callbacks
	lu5_register_event_callbacks(window);

	LU5_RUN_LOG("draw");

	lu5.env.last_time = glfwGetTime();

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{

		// Update environement values
		lu5.env.now_time = glfwGetTime();
		lu5.env.delta_time = (lu5.env.now_time - lu5.env.last_time);
		glfwPollEvents();		

		lu5_update_dynamic_variables(&lu5, window);

		// If no target framerate, draw
		if (lu5.env.target_framerate == -1) 
		{
			lu5_draw(&lu5, window);
		} 
		else 
		{
			// Check if should render
			if((lu5.env.now_time - lu5.env.last_frame_time) >= (1.0 / lu5.env.target_framerate)) 
			{
				// TODO: handle events in `./src/lu5_event_callbacks.c` the same way
				lu5_draw(&lu5, window);

				// Record for framerate
				lu5.env.last_frame_time = lu5.env.now_time;
			}
		}

		// Record for delta_time
		lu5.env.last_time = lu5.env.now_time;
	}

	LU5_INFO(LU5_EXIT_APP);

cleanup:

	glfwTerminate();

	lu5_close(&lu5);
	
	return 0;
}
