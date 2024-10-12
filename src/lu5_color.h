#ifndef _LU5_COLOR_H_
#define _LU5_COLOR_H_

#include <lua.h>
#include <stdint.h>

typedef union
{
	uint32_t hexadecimal;
	uint8_t bytearray[4];

	struct 
	{
		uint8_t a;
		uint8_t b;
		uint8_t g;
		uint8_t r;
	};
} lu5_color;

#ifndef LU5_WASM

#define lu5_apply_color(c1)\
	glColor4ub(\
		c1.r,\
		c1.g,\
		c1.b,\
		c1.a\
	);\

#endif

#define lu5_color_visible(c) (c.a)
#define LU5_RGBA(sr,sg,sb,sa) ((lu5_color){ .r=sr, .g=sg, .b=sb, .a=sa })

#define LU5_WHITE LU5_RGBA(255, 255, 255, 255)
#define LU5_BLACK LU5_RGBA(  0,   0,   0, 255)
#define LU5_GREY  LU5_RGBA( 51,  51,  51, 255)


typedef struct {
	const char *name;
	lu5_color color;
} lu5_labeled_color;

void lu5_register_colors(lua_State *L);

lu5_color lu5_args_to_color(lua_State *L);

#define LU5_COLOR_COUNT 12
extern lu5_labeled_color lu5_known_colors[];

#endif
