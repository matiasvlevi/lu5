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
} Color;

Color rgbColorFromLuaArguments(lua_State *L);

#endif
