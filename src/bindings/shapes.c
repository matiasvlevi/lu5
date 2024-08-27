#include "shapes.h"

#include "../lu5_state.h"
#include "../lu5_font.h"
#include "../lu5_image.h"
#include "../lu5_types.h"

#include "../geometry/lu5_geometry.h"

#include <lauxlib.h>
#include <math.h>
#include "lu5_math.h"

int beginShape(lua_State *L) 
{
	lua_Integer shape_type = lu5_assert_integer(L, 1, "beginShape");

	lu5_apply_color(lu5.style.fill);
	glBegin(shape_type);

	return 0;
}

int vertex(lua_State *L) 
{
	lua_Number x = lu5_assert_number(L, 1, "vertex");
	lua_Number y = lu5_assert_number(L, 2, "vertex");

	glVertex2f(x, y);
	return 0;
}

int endShape(lua_State *L)
{
	glEnd();
	return 0;
}

int circle(lua_State *L) 
{
	lua_Number x = lu5_assert_number(L, 1, "circle");  
	lua_Number y = lu5_assert_number(L, 2, "circle");
	lua_Number d = lu5_assert_number(L, 3, "circle");

	float radius = d / 2.0f;

	if (lu5_has_fill())
	{
		lu5_apply_color(lu5.style.fill);

		lu5_render_ellipse(x, y, radius, radius, LU5_CIRCLE_SEGMENTS);
	}

	if (lu5_has_stroke()) 
	{
		lu5_apply_color(lu5.style.stroke);

		lu5_render_ring(x, y, radius, radius + lu5.style.strokeWeight, LU5_CIRCLE_SEGMENTS);
	}
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

	float x2 = x + w;
	float y2 = y + h;

	if (lu5_has_stroke()) 
	{
		lu5_apply_color(lu5.style.stroke);

		glBegin(GL_QUADS);
			glVertex2f( x - lu5.style.strokeWeight,  y - lu5.style.strokeWeight);
			glVertex2f(x2 + lu5.style.strokeWeight,  y - lu5.style.strokeWeight);
			glVertex2f(x2 + lu5.style.strokeWeight, y2 + lu5.style.strokeWeight);
			glVertex2f( x - lu5.style.strokeWeight, y2 + lu5.style.strokeWeight);
		glEnd(); 
	}

	if (lu5_has_fill()) 
	{
		lu5_apply_color(lu5.style.fill);
		glBegin(GL_QUADS);
			glVertex2f(x, y);
			glVertex2f(x2, y);
			glVertex2f(x2, y2);
			glVertex2f(x, y2);
		glEnd();
	}

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

	float dx = x2 - x1;
	float dy = y2 - y1;
	float length = sqrt(dx * dx + dy * dy);

	float strokeWeight = ((float)lu5.style.strokeWeight / 2);

	float nx = strokeWeight * ( dy / length);
	float ny = strokeWeight * (-dx / length);

	lu5_apply_color(lu5.style.stroke);
	glBegin(GL_QUADS);
		glVertex2f(x1 - nx, y1 - ny);
		glVertex2f(x1 + nx, y1 + ny);
		glVertex2f(x2 + nx, y2 + ny);
		glVertex2f(x2 - nx, y2 - ny);
	glEnd();

	if (lu5.style.strokeWeight >= 3) 
	{
		lu5_render_ellipse(x1, y1, strokeWeight, strokeWeight, LINE_POINT_SEGMENTS);
		lu5_render_ellipse(x2, y2, strokeWeight, strokeWeight, LINE_POINT_SEGMENTS);
	};

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

	lu5_apply_color(lu5.style.fill);
	glBegin(GL_QUADS);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x3, y3);
		glVertex2f(x4, y4);
	glEnd(); 

	return 0;
}

int point(lua_State *L)
{
	lua_Number x = lu5_assert_number(L, 1, "point");
	lua_Number y = lu5_assert_number(L, 2, "point");

	// refer to https://p5js.org/reference/#/p5/point

	luaL_error(L, "TODO: Implement point.\t point(%f, %f);", x, y);
	return 0;
}

int triangle(lua_State *L)
{
	lua_Number x1 = lu5_assert_number(L, 1, "triangle");
	lua_Number y1 = lu5_assert_number(L, 2, "triangle");
	// ... more arguments
	// refer to https://p5js.org/reference/#/p5/triangle

	luaL_error(L, "TODO: Implement triangle.\t triangle(%f, %f, ...more args);", x1, y1);
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

	if (lu5_has_stroke()) 
	{
		lu5_apply_color(lu5.style.stroke);

		lu5_render_ellipse(x, y, w + lu5.style.strokeWeight, h + lu5.style.strokeWeight, LU5_CIRCLE_SEGMENTS);
	}

	if (lu5_has_fill())
	{
		lu5_apply_color(lu5.style.fill);

		lu5_render_ellipse(x, y, w, h, LU5_CIRCLE_SEGMENTS);
	}

	return 0;
}

int arc(lua_State *L)
{
	lua_Number x = lu5_assert_number(L, 1, "arc");
	lua_Number y = lu5_assert_number(L, 2, "arc");

	lua_Number w = lu5_assert_number(L, 3, "arc");
	lua_Number h = lu5_assert_number(L, 4, "arc");

	lua_Number sa = lu5_assert_number(L, 5, "arc");
	lua_Number ea = lu5_assert_number(L, 6, "arc");

	if (lu5_has_fill())
	{
		lu5_apply_color(lu5.style.fill);
		lu5_render_arc_fill(
			x, y, 
			w, h, 
			sa, ea, 
			LU5_CIRCLE_SEGMENTS);
	}

	if (lu5_has_stroke())
	{
		lu5_apply_color(lu5.style.stroke);
		glLineWidth(lu5.style.strokeWeight);
		lu5_render_arc_stroke(
			x, y, 
			w, h, 
			w + lu5.style.strokeWeight, 
			h + lu5.style.strokeWeight, 
			sa, ea, 
			LU5_CIRCLE_SEGMENTS
		);
	}

	return 0;
}
