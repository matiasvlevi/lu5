#include "setting.h"

#include <lauxlib.h>

#include "../lu5_window.h"

#include "../lu5_state.h"
#include "../lu5_types.h"

#include "../lu5_geometry.h"
#include "../lu5_fs.h"
#include "../lu5_font.h"

int background(lua_State *L) 
{
	lu5_color color = lu5_args_to_color(L);

	lu5_background(color);

	return 0;
}

int strokeWeight(lua_State *L) 
{
	lua_Number weight = lu5_assert_number(L, 1, "strokeWeight");
	
	lu5_style(&lu5)->strokeWeight = weight;

	return 0;
}

int fill(lua_State *L) 
{
	lu5_color color = lu5_args_to_color(L);

	lu5_style(&lu5)->fill = color;

	return 0;
}

int noFill(lua_State *L) 
{
	lu5_style(&lu5)->fill = LU5_RGBA(0, 0, 0, 0);

	return 0;
}

int stroke(lua_State *L) 
{
	lu5_color color = lu5_args_to_color(L); 

	lu5_style(&lu5)->stroke = color;
	
	return 0;
}

int noStroke(lua_State *L) 
{
	lu5_style(&lu5)->stroke = LU5_RGBA(0, 0, 0, 0);

	return 0;
}

int push(lua_State *L) 
{
	lu5_style_setting blank = {};
	lu5_set_style(&blank);

	lu5_style(&lu5)->fill   = LU5_WHITE;
	lu5_style(&lu5)->stroke = LU5_BLACK;
	
	lu5_style_push(&lu5, &blank);

	glPushMatrix();
	
	return 0;
}

int pop(lua_State *L) 
{
	lu5_style_pop(&lu5);

	glPopMatrix();

	return 0;
}

int rectMode(lua_State *L) 
{
	lua_Integer mode = lu5_assert_integer(L, 1, "rectMode");

	if (mode <= LU5_RECT_ALIGN_MODE_COUNT)
	{
		lu5_style(&lu5)->rectMode = mode;
	} else {
		LU5_WARN("rectMode with mode '%i' is invalid", mode);
	}
	return 0;
}

int debugMode(lua_State *L)
{
	if (lua_isboolean(L, 1)) 
	{
		lu5.debug = lua_toboolean(L, 1);
	} else {
		lu5.debug = true;
	}

	return 0;
}