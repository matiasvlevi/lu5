#ifndef _LU5_BINDINGS_H_
#define _LU5_BINDINGS_H_

#include <lua.h>
#include <GLFW/glfw3.h>
#include "lu5_state.h"

#define LUA_ADD_BOOL_GLOBAL(l, name)				  lua_pushboolean(l, name); lua_setglobal(l, #name)
#define LUA_ADD_BOOL_GLOBAL_BY_NAME(l, name, value)   lua_pushboolean(l, value); lua_setglobal(l, name)


#define LUA_ADD_STRING_GLOBAL(l, name)				  lua_pushstring(l, name); lua_setglobal(l, #name)
#define LUA_ADD_STRING_GLOBAL_BY_NAME(l, name, value) lua_pushstring(l, value); lua_setglobal(l, name)

#define LUA_ADD_NUMBER_GLOBAL(l, name)		          lua_pushnumber(l, name); lua_setglobal(l, #name)
#define LUA_ADD_NUMBER_GLOBAL_BY_NAME(l, name, value) lua_pushnumber(l, value); lua_setglobal(l, name)

#define LUA_ADD_FUNCTION(l, name)					  lua_pushcfunction(l, name); lua_setglobal(l, #name)
#define LUA_ADD_FUNCTION_BY_NAME(l, name, func)		  lua_pushcfunction(l, func); lua_setglobal(l, name)

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
