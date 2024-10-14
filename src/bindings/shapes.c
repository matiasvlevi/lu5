#include "shapes.h"

#include "../lu5_state.h"
#include "../lu5_types.h"

#include "../lu5_geometry.h"
#include "../lu5_fs.h"
#include "../lu5_font.h"
#include "../lu5_image.h"

#include <lauxlib.h>
#include <math.h>
#include "lu5_math.h"

int beginShape(lua_State *L) 
{
	lua_Integer shape_type = GL_LINES;
	if (lua_isinteger(L, 1)) {
		shape_type = lua_tointeger(L, 1);
	}

	lu5_2D_over_3D_begin(lu5.depth_mode, lu5.width, lu5.height);
	
	lu5_glBegin(shape_type, lu5_style(&lu5)->fill);

	return 0;
}

int vertex(lua_State *L) 
{
	lua_Number x = lu5_assert_number(L, 1, "vertex");
	lua_Number y = lu5_assert_number(L, 2, "vertex");

	lu5_glVertex2(x, y);
	return 0;
}

int endShape(lua_State *L)
{
	lu5_glEnd();
	
	lu5_2D_over_3D_end(lu5.depth_mode);

	return 0;
}

int rect(lua_State *L) 
{
	lua_Number x = lu5_assert_number(L, 1, "rect");  
	lua_Number y = lu5_assert_number(L, 2, "rect");  
	lua_Number w = lu5_assert_number(L, 3, "rect");  

	lua_Number h = w;
	if (lua_isnumber(L, 4)) {
		h = lu5_assert_number(L, 4, "rect");
	}  

	float x2;
	float y2;

	switch(lu5_style(&lu5)->rectMode) 
	{
		case LU5_RECTMODE_CORNER:
			x2 = x + w;
			y2 = y + h;
			break;
		case LU5_RECTMODE_CENTER:
			w = w / 2;
			h = h / 2;
			// Intentionally continue in Radius's case
		case LU5_RECTMODE_RADIUS:
			x2 = x + w;
			y2 = y + h;

			x -= w;
			y -= h;
			break;
		default:
			luaL_error(L, "Something went wrong with rectMode, mode found %d", lu5_style(&lu5)->rectMode);
			break;
	}

	lu5_2D_over_3D_begin(lu5.depth_mode, lu5.width, lu5.height);

	lu5_render_quad(
		x, y, x2, y, 
		x2, y2, x, y2, 
		lu5_style(&lu5)->strokeWeight,
		lu5_style(&lu5)->fill, 
		lu5_style(&lu5)->stroke);

	lu5_2D_over_3D_end(lu5.depth_mode);

	return 0;
}

int square(lua_State *L)
{
	if (lua_gettop(L) != 3) {
		luaL_error(L, "square expects 3 arguments");
		return 0;
	}

	rect(L);

	return 0;
}

int line(lua_State *L) 
{
	lua_Number x1 = lu5_assert_number(L, 1, "line");
	lua_Number y1 = lu5_assert_number(L, 2, "line");
	lua_Number x2 = lu5_assert_number(L, 3, "line");
	lua_Number y2 = lu5_assert_number(L, 4, "line");

	lu5_2D_over_3D_begin(lu5.depth_mode, lu5.width, lu5.height);

	lu5_render_line(x1, y1, x2, y2, 
		(float)lu5_style(&lu5)->strokeWeight / 2,
		lu5_style(&lu5)->stroke);

	lu5_2D_over_3D_end(lu5.depth_mode);

	return 0;
}

int quad(lua_State *L)
{
	int argc;
	if ((argc = lua_gettop(L)) != 8) {
		luaL_error(L, "Expected 8 arguments got %i instead", argc);
		return 0;
	}

	lua_Number x1 = lu5_assert_number(L, 1, "quad");
	lua_Number y1 = lu5_assert_number(L, 2, "quad");
	lua_Number x2 = lu5_assert_number(L, 3, "quad");
	lua_Number y2 = lu5_assert_number(L, 4, "quad");
	lua_Number x3 = lu5_assert_number(L, 5, "quad");
	lua_Number y3 = lu5_assert_number(L, 6, "quad");
	lua_Number x4 = lu5_assert_number(L, 7, "quad");
	lua_Number y4 = lu5_assert_number(L, 8, "quad");

	lu5_2D_over_3D_begin(lu5.depth_mode, lu5.width, lu5.height);
	
	lu5_render_quad(
		x1, y1, 
		x2, y2, 
		x3, y3, 
		x4, y4, 
		lu5_style(&lu5)->strokeWeight,
		lu5_style(&lu5)->fill,
		lu5_style(&lu5)->stroke);

	lu5_2D_over_3D_end(lu5.depth_mode);

	return 0;
}

int triangle(lua_State *L)
{
	lua_Number x1 = lu5_assert_number(L, 1, "triangle");
	lua_Number y1 = lu5_assert_number(L, 2, "triangle");
	
	lua_Number x2 = lu5_assert_number(L, 3, "triangle");
	lua_Number y2 = lu5_assert_number(L, 4, "triangle");

	lua_Number x3 = lu5_assert_number(L, 5, "triangle");
	lua_Number y3 = lu5_assert_number(L, 6, "triangle");

	lu5_render_triangle(x1, y1, x2, y2, x3, y3, 
		lu5_style(&lu5)->strokeWeight,
		lu5_style(&lu5)->fill,
		lu5_style(&lu5)->stroke);

	return 0;
}

int ellipse(lua_State *L)
{
	lua_Number x = lu5_assert_number(L, 1, "ellipse");
	lua_Number y = lu5_assert_number(L, 2, "ellipse");
	
	lua_Number w = lu5_assert_number(L, 3, "ellipse");
	lua_Number h = w;
	if (lua_isnumber(L, 4)) {
		h = lua_tonumber(L, 4);
	}

	w /= 2.0f;
	h /= 2.0f;

	lu5_2D_over_3D_begin(lu5.depth_mode, lu5.width, lu5.height);

	lu5_render_ellipse(x, y, w, h, 
		lu5_style(&lu5)->strokeWeight, 
		lu5_style(&lu5)->fill, 
		lu5_style(&lu5)->stroke,
		LU5_CIRCLE_SEGMENTS);

	lu5_2D_over_3D_end(lu5.depth_mode);

	return 0;
}

int circle(lua_State *L) 
{
	if (lua_gettop(L) != 3) {
		luaL_error(L, "circle expects 3 arguments");
		return 0;
	}
	
	ellipse(L);

	return 0;
}

int arc(lua_State *L)
{
	lua_Number x = lu5_assert_number(L, 1, "arc");
	lua_Number y = lu5_assert_number(L, 2, "arc");

	lua_Number w = lu5_assert_number(L, 3, "arc");
	lua_Number h = lu5_assert_number(L, 4, "arc");

	lua_Number start_angle = lu5_assert_number(L, 5, "arc");
	lua_Number end_angle = lu5_assert_number(L, 6, "arc");

	lu5_render_arc(
		x, y, 
		w, h, 
		lu5_style(&lu5)->strokeWeight,
		start_angle, end_angle,
		LU5_CIRCLE_SEGMENTS,
		lu5_style(&lu5)->fill,
		lu5_style(&lu5)->stroke);

	return 0;
}

int point(lua_State *L)
{
	lua_Number x = lu5_assert_number(L, 1, "point");
	lua_Number y = lu5_assert_number(L, 2, "point");

	lu5_2D_over_3D_begin(lu5.depth_mode, lu5.width, lu5.height);

	if (lu5_has_stroke())
	{
		lu5_render_ellipse_fill(x, y,
			lu5_style(&lu5)->strokeWeight,
			lu5_style(&lu5)->strokeWeight,
			lu5_style(&lu5)->stroke,
			LU5_CIRCLE_SEGMENTS);
	}

	lu5_2D_over_3D_end(lu5.depth_mode);
	return 0;
}