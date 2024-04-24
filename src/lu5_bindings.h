#ifndef __LU5_BINDINGS__
#define __LU5_BINDINGS__

#include <lua.h>
#include <GLFW/glfw3.h>

/**
 * Updates global variables mouseX, mouseY, mouseIsPressed
 * 
 * @param L 
 * @param window 
 */
void lu5_update_dynamic_variables(lua_State *L, GLFWwindow *window);

/**
 * Registers all of the binding symbols into the lua state
 * 
 * @param L 
 */
void lu5_register_symbols(lua_State *L);

#endif
