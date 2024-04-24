#ifndef __COLOR_ARGS_H__
#define __COLOR_ARGS_H__

#include <lua.h>
#include <stdint.h>

typedef union
{
	uint32_t hexadecimal;
	uint8_t bytearray[4];

	struct 
	{
		uint8_t b;
		uint8_t g;
		uint8_t r;
		uint8_t a; 
	};
} lu5_color;

// TODO: Turn this into a function and use lu5_color
#define GET_COLOR_FROM_LUA_ARGS(l)\
    double r = lua_tonumber(L, 1);\
    double g = r;\
    if(lua_gettop(l) > 1) g = lua_tonumber(L, 2);\
    double b = r;\
    if(lua_gettop(l) > 2) b = lua_tonumber(L, 3);\
    double a = 0xFF; \
    if(lua_gettop(l) > 3) a = lua_tonumber(L, 4)

lu5_color rgbColorFromLuaArguments(lua_State *L);

#endif
