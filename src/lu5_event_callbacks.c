#include "lu5_event_callbacks.h"
#include "lu5_state.h"

#include "lu5_logger.h"
#include "bindings/mouse.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "./lu5_core.h"
#include "./lu5_window.h"

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) 
{
	if (!lu5.L) return;

	lu5.input.mouse.actions[button] = action;
  
	if (action == 1) {
		lua_getglobal(lu5.L, LU5_MOUSE_PRESSED);
	} else {
		lua_getglobal(lu5.L, LU5_MOUSE_RELEASED);
	}

	if (lua_isfunction(lu5.L, -1)) {
		lua_pushinteger(lu5.L, button);

		if (lua_pcall(lu5.L, 1, 0, 0) != LUA_OK) {
			LU5_ERROR(lua_tostring(lu5.L, -1));
		}
	}
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	errno = 0;
	if (!lu5.L) return;

	switch(action) {
		case GLFW_RELEASE: 
			lu5.input.keyboard.current_keys[key] = GLFW_RELEASE;
			lu5.input.keyboard.is_down[key] = false;

			// Get keyReleased
			lua_getglobal(lu5.L, "keyReleased");
			break;
		case GLFW_PRESS:
			// Restart key (CTRL + R)
			if (key == GLFW_KEY_R && (mods & GLFW_MOD_CONTROL)) 
			{
				LU5_INFO("Refreshing sketch");
				lu5.env.restart = true;
			}

			lu5.input.keyboard.current_keys[key] = GLFW_PRESS;
			lu5.input.keyboard.is_down[key] = true;
			
			// Get keyPressed
			lua_getglobal(lu5.L, "keyPressed");
			break;
		case GLFW_REPEAT:
			lu5.input.keyboard.current_keys[key] = GLFW_REPEAT;
			
			// Get keyHeld
			lua_getglobal(lu5.L, "keyHeld");
			break;
	}

	// Check if callback event is a function
	if (lua_isfunction(lu5.L, -1)) {
		const char *name = glfwGetKeyName(key, scancode);
		size_t key_name_length;

		// No name found (special key: ctrl, enter, shift, etc)
		if (name == NULL) 
		{
			// Push event arguments (key, keyCode)
			lua_pushnil(lu5.L);
			lua_pushinteger(lu5.L, key);

			// Call event callback
			if (lua_pcall(lu5.L, 2, 0, 0) != LUA_OK) {
				LU5_ERROR(lua_tostring(lu5.L, -1));
			}
			return;
		} else {
			key_name_length = strlen(name);
		}

		char *key_name = (char*)malloc(key_name_length);

		// Is letter character
		if (key >= 65 && key <= 90) {
			
			// is letter & lower case
			bool is_lowercase =
				((mods & GLFW_MOD_CAPS_LOCK) ||
				(mods & GLFW_MOD_SHIFT));

			// Format key character to string
			int err = sprintf(key_name, "%c", is_lowercase ? key : (key + 32));
			if (err == -1) {
				LU5_ERROR("%s", strerror(errno));

				if (key_name != NULL)
					free(key_name);

				return;
			}
		} else {
			// is not letter character

			// Format key name as string for edge cases
			int err = sprintf(key_name, "%s", name);
			if (err == -1) {
				LU5_ERROR("%s", strerror(errno));
				
				if (key_name != NULL)
					free(key_name);
				
				return;
			}
		}

		// Push event arguments (key, keyCode)
		lua_pushlstring(lu5.L, key_name, 1);
		lua_pushinteger(lu5.L, key);

		// Call event callback
		if (lua_pcall(lu5.L, 2, 0, 0) != LUA_OK) {
			LU5_ERROR(lua_tostring(lu5.L, -1));
		}

		if (key_name != NULL)
			free(key_name);
	}
}

void lu5_register_event_callbacks(GLFWwindow *window) 
{
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetInputMode(window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);
	
	return;
}
	



