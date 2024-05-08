#ifndef __DEFS_H__
#define __DEFS_H__

#include "lu5_logger.h"

#define LUA_ADD_BOOL_GLOBAL(l, name)			            lua_pushboolean(l, name); lua_setglobal(l, #name)

#define LUA_ADD_STRING_GLOBAL(l, name)		                lua_pushstring(l, name); lua_setglobal(l, #name)
#define LUA_ADD_STRING_GLOBAL_BY_NAME(l, name, value)		lua_pushstring(l, value); lua_setglobal(l, name)

#define LUA_ADD_NUMBER_GLOBAL(l, name)		                lua_pushnumber(l, name); lua_setglobal(l, #name)
#define LUA_ADD_NUMBER_GLOBAL_BY_NAME(l, name, value)		lua_pushnumber(l, value); lua_setglobal(l, name)

#define LUA_ADD_FUNCTION(l, name)					        lua_pushcfunction(l, name); lua_setglobal(l, #name)
#define LUA_ADD_FUNCTION_BY_NAME(l, name, func)		        lua_pushcfunction(l, func); lua_setglobal(l, name)

#define LU5_SKETCH_BOILERPLATE \
		"\n"\
		"function setup()\n"\
		"   createWindow(600, 600);\n"\
		"end\n"\
		"\n"\
		"function draw()\n"\
		"   background(51);\n"\
		"end\n"\

#endif
