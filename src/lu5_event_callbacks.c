#include "lu5_event_callbacks.h"
#include "lu5_state.h"

#include "lu5_logger.h"
#include "bindings/mouse.h"

#include <stdio.h>

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
	if (!lu5.L) return;

	switch(action) {
		case GLFW_RELEASE: 
			lu5.input.keyboard.current_keys[key] = GLFW_RELEASE;
			lu5.input.keyboard.is_down[key] = false;

			// Get keyReleased
			lua_getglobal(lu5.L, "keyReleased");
			break;
		case GLFW_PRESS: 
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
		char key_string[2] = {};

		if (key >= 65 && key <= 90) {
			bool is_upper = 
				(mods & GLFW_MOD_CAPS_LOCK) ||
				(mods & GLFW_MOD_SHIFT);

			int err = sprintf(key_string, "%c", is_upper ? key : (key + 32));
		}

		lua_pushinteger(lu5.L, key);
		lua_pushlstring(lu5.L, key_string, 1);

		if (lua_pcall(lu5.L, 2, 0, 0) != LUA_OK) {
			LU5_ERROR(lua_tostring(lu5.L, -1));
		}
	}

}


void lu5_register_event_callbacks(GLFWwindow *window) 
{
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, key_callback);

	return;
}
	



