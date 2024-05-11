#include "setting.h"

#include <lauxlib.h>

#include "../lu5_state.h"
#include "../lu5_font.h"

int strokeWeight(lua_State *L) 
{
	double weight = lua_tonumber(L, 1);

	glLineWidth(weight);
	
	lu5.style.strokeWeight = weight;

	return 0;
}

int fill(lua_State *L) 
{
	lu5_color color = lu5_args_to_color(L);

	lu5.style.fill = color;

	return 0;
}

int noFill(lua_State *L) 
{
	lu5.style.fill = (lu5_color){ .r=0, .g=0, .b=0, .a=0 };

	return 0;
}

int stroke(lua_State *L) 
{
	lu5_color color = lu5_args_to_color(L); 

	lu5.style.stroke = color;

	return 0;
}

int noStroke(lua_State *L) 
{
	lu5.style.stroke = (lu5_color){ .r=0, .g=0, .b=0, .a=0 };

	return 0;
}

int textSize(lua_State *L)
{
	double size = lua_tonumber(L, 1);

	// Get font, if none available, use default.
	lu5_font *font = lu5.style.font_current;
	if (font == NULL) {
		font = lu5.font_default;
	}

	FT_Set_Char_Size(
		font->face,
		0,
		size * 64,
		0,
		0
	);

	lu5.style.fontSize = size;

	return 0;
}


int textFont(lua_State *L)
{
	// Check if valid
	if (!lua_islightuserdata(L, 1)) {
		luaL_error(L, "Expected first argument to be a font ptr");
	
		return 0;
	}

	// Get the font ptr
	lu5_font *font_id = (lu5_font *)lua_touserdata(L, 1);
	
	// Set the current font ptr
	lu5.style.font_current = font_id;

	return 0;
}

int push(lua_State *L) 
{
	lu5.style_cache = lu5.style;
	lu5.style = LU5_DEFAULT_STYLE;
	return 0;
}

int pop(lua_State *L) 
{
	lu5.style = lu5.style_cache;
	lu5.style_cache = LU5_DEFAULT_STYLE;
	return 0;
}
