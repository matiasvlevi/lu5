#ifndef _LU5_BINDINGS_H_
#define _LU5_BINDINGS_H_

#include <lua.h>

#define LUA_ADD_BOOL_GLOBAL(l, name)				  lua_pushboolean(l, name); lua_setglobal(l, #name)
#define LUA_ADD_BOOL_GLOBAL_BY_NAME(l, name, value)   lua_pushboolean(l, value); lua_setglobal(l, name)

#define LUA_ADD_STRING_GLOBAL(l, name)				  lua_pushstring(l, name); lua_setglobal(l, #name)
#define LUA_ADD_STRING_GLOBAL_BY_NAME(l, name, value) lua_pushstring(l, value); lua_setglobal(l, name)

#define LUA_ADD_NUMBER_GLOBAL(l, name)		          lua_pushnumber(l, name); lua_setglobal(l, #name)
#define LUA_ADD_NUMBER_GLOBAL_BY_NAME(l, name, value) lua_pushnumber(l, (lua_Number)value); lua_setglobal(l, name)

#define LUA_ADD_INTEGER_GLOBAL(l, name)		          lua_pushinteger(l, name); lua_setglobal(l, #name)
#define LUA_ADD_INTEGER_GLOBAL_BY_NAME(l, name, value) lua_pushinteger(l, (lua_Integer)value); lua_setglobal(l, name)

#define LUA_ADD_FUNCTION(l, name)					  lua_pushcfunction(l, name); lua_setglobal(l, #name)
#define LUA_ADD_FUNCTION_BY_NAME(l, name, func)		  lua_pushcfunction(l, func); lua_setglobal(l, name)

#define LU5_ONE_TO_ONE_BINDING(lib, name, ret)\
	int argc = lua_gettop(L);\
	lua_getglobal(L, lib);\
	lua_getfield(L, -1, name);\
	for (int i = 1; i <= argc; i++) {\
		lua_pushvalue(L, i);\
	}\
	lua_call(L, argc, ret);

/**
 * Registers all of the binding symbols into the lua state
 * 
 * @param L 
 */
void lu5_register_symbols(lua_State *L);

#endif
