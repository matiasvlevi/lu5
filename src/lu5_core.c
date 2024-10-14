#include "lu5_core.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "lu5_bindings.h"
#include "lu5_event_callbacks.h"
#include "lu5_color.h"
#include "lu5_types.h"

#include "lu5_random.h"
#include "lu5_font.h"

#include "lu5_geometry.h"
#include "lu5_image.h"
#include "lu5_obj.h"

#include "bindings/mouse.h"
#include "bindings/window.h"

#ifdef LU5_WASM
#define LU5_EXCEPTION_TAG_INDEX 1
#endif

lu5_State *lu5_get_handle(void) 
{
	return &lu5;
}

static jmp_buf lu5_panic_jump;
static int lu5_panic(lua_State *L)
{
	const char *str = lua_tostring(L, -1);
	LU5_ERROR("%s", str);

	#ifndef LU5_WASM
	_longjmp(lu5_panic_jump, 1);
	#else
	int data = 0;
	__builtin_wasm_throw(LU5_EXCEPTION_TAG_INDEX, &data);
	#endif
    return 0;
}

void lu5_init(lu5_State *l5)
{
	lu5_init_state(l5);

	l5->L = luaL_newstate();
	lua_atpanic(l5->L, &lu5_panic);

	luaL_openlibs(l5->L);
	lu5_init_freetype(l5);
	
	// When log level is set to DEBUG (gt than 5)
	// lu5 will log integer and number types at startup
	lu5_log_types();

	// Register functions & constants
	lu5_register_symbols(l5->L);
	lu5_register_colors(l5->L);

	lua_Integer seed = lu5_time_seed();
	
	// Set the random seed
	lua_getglobal(l5->L, "math");
	lua_getfield(l5->L, -1, "randomseed");
	lua_pushinteger(l5->L, seed);
	lua_call(l5->L, 1, 0);

	l5->env.restart_time = clock();

	l5->log_level = LU5_WARN_LOG;

	#ifdef LU5_WASM
		lua_pushboolean(l5->L, true);
	#else
		lua_pushboolean(l5->L, false);
	#endif
	lua_setglobal(l5->L, "WEB");

	return;
}

int lu5_run_setup(lu5_State *l5) 
{
	// Get the setup function, if found, run it
	lua_getglobal(l5->L, "setup");
	if (lua_isfunction(l5->L, -1)) 
	{
		#ifndef LU5_WASM
		LU5_RUN_LOG("setup");
		#endif

		// Run Setup
		lua_getglobal(l5->L, "setup"); 
		if (lua_pcall(l5->L, 0, 0, 0) != LUA_OK) {
			return 1;
		}
	}
	return 0;
}

static void lu5_run_draw(lu5_State *l5) 
{
	if (l5->loop) 
	{
		lua_getglobal(l5->L, "draw");

		if (lua_pcall(l5->L, 0, 0, 0) != LUA_OK) 
		{
			// EXIT
			luaL_error(l5->L, lua_tostring(l5->L, -1));
		} 
		else if (l5->debug)
		{
			if (l5->depth_mode == LU5_GL3D) lu5_render_debug();
			// else lu5_render_debug_2D(); // TODO:
		}

		glfwSwapBuffers(l5->window);
	}

	// Still allow polling events for Restarts
	glfwPollEvents();
	
}

int lu5_run_sketch(lu5_State *l5, const char *filename, const char *source)
{
	if (setjmp(lu5_panic_jump) != 0) return 1;

	// Add `sketch` as a string variable holding the filename
	lua_pushstring(l5->L, (filename == NULL) ? "canvas" : filename);
	lua_setglobal(l5->L, "sketch");

	// Print Running log
	if (filename != NULL) {
		LU5_RUN_LOG(filename);
	}

	// // Run the file or source string
	int result = (filename == NULL) ? 
		 luaL_dostring(l5->L, source) :
		 luaL_dofile(l5->L, filename) ;
	
	if (result != LUA_OK) 
	{
		const char *msg = lua_tostring(l5->L, -1);
		luaL_error(l5->L, msg);
		return 1;
	}


	// Get the setup function, if found, run it
	// if None found, ignore
	if (lu5_run_setup(l5)) {
		// Setup threw an error
		luaL_error(l5->L, lua_tostring(l5->L, -1));
		return 1; 
	}

	// Get the draw function, if not found, exit
	lua_getglobal(l5->L, "draw");
	if (!lua_isfunction(l5->L, -1)) {
		return 2;
	}

	#ifndef LU5_WASM
		// Check if window was created from lua,
		// not found, exit
		lua_getglobal(l5->L, "window");
		if (!lua_isuserdata(l5->L, -1)) {
			LU5_WARN(LU5_NO_WINDOW);
			return 1;
		}

		// Window global was defined
		lu5_window *window = (lu5_window*)lua_touserdata(l5->L, -1);
		// not found, exit
		if (window == NULL) {
			luaL_error(l5->L, LU5_INVALID_WINDOW);
			return 0;
		};	
		l5->window = window;

		// Register Event Callbacks
		lu5_register_event_callbacks(l5);
	#else
		void *window = NULL;
	#endif

	// Set window mouse values before calling draw
	double width = 0.0, height = 0.0;
	glfwGetCursorPos(window, &width, &height);
	
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(l5->L, LU5_PMOUSE_X, width);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(l5->L, LU5_PMOUSE_Y, height);

	LUA_ADD_NUMBER_GLOBAL_BY_NAME(l5->L, LU5_MOUSE_X, width);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(l5->L, LU5_MOUSE_Y, height);

	#ifndef LU5_WASM
		l5->env.restart = false;
	
		LU5_RUN_LOG("draw");

		l5->env.last_time = glfwGetTime();
		// Loop until the user closes the window
		while (!glfwWindowShouldClose(window) && !l5->env.restart)
		{
			// Update environement values
			l5->env.now_time = glfwGetTime();

			l5->env.delta_time = (l5->env.now_time - l5->env.last_time);

			// If no target framerate, draw
			if (l5->env.target_framerate == -1) 
			{
				// For free frame rates
				LUA_ADD_NUMBER_GLOBAL_BY_NAME(l5->L, LU5_DELTA_TIME, 
					(lua_Number)l5->env.delta_time);

				lu5_run_draw(l5);
			} 
			else 
			{
				LUA_ADD_NUMBER_GLOBAL_BY_NAME(l5->L, LU5_DELTA_TIME, 
					(lua_Number)(lu5.env.now_time - lu5.env.last_frame_time));

				// Check if should render
				if((l5->env.now_time - l5->env.last_frame_time) >= (1.0 / l5->env.target_framerate)) 
				{
					// TODO: handle events in `./src/lu5_event_callbacks.c` the same way
					lu5_run_draw(l5);

					// Record for framerate
					l5->env.last_frame_time = l5->env.now_time;
				}
			}

			// Record for delta_time
			l5->env.last_time = l5->env.now_time;
		}

		lu5_close(l5);
	#endif

	return 0;
}

void lu5_animation_frame(lu5_State *l5, float delta_time)
{
	lu5.env.delta_time = delta_time;
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(l5->L, LU5_DELTA_TIME, (lua_Number)(lu5.env.delta_time));

	lu5_run_draw(l5);
	
}

void lu5_close(lu5_State *l5) 
{
	#ifndef LU5_WASM
	lu5_close_images(l5);

	lu5_close_models(l5);

	lu5_close_fonts(l5);
	
	if (l5->orbit != NULL) {
		free(l5->orbit);
		l5->orbit = NULL;
	}
	#endif

	lu5_style_clear(l5);

	if (l5->L != NULL) {
		lua_gc(l5->L, LUA_GCCOLLECT, 0);
		lua_close(l5->L);
		l5->L = NULL;
	}
}
