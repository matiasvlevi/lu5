#ifndef __LU5_BINDINGS__
#define __LU5_BINDINGS__

#include <lua.h>
#include <GLFW/glfw3.h>
#include "lu5_state.h"
/**
 * Updates global variables mouseX, mouseY, mouseIsPressed
 * 
 * @param L 
 * @param window 
 */
void lu5_update_dynamic_variables(lu5_State *l5, GLFWwindow *window);

/**
 * Registers all of the binding symbols into the lua state
 * 
 * @param L 
 */
void lu5_register_symbols(lua_State *L);

void lu5_register_number_array(lua_State *L, const char* array_name, double *list, size_t size);
void lu5_register_integer_array(lua_State *L, const char* array_name, int *list, size_t size);
void lu5_register_string_array(lua_State *L, const char* array_name, const char **list, size_t size);

#endif
