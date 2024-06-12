#include "shapes.h"

#include "../lu5_state.h"
#include "../lu5_font.h"
#include "../lu5_image.h"
#include "../lu5_types.h"

#include <lauxlib.h>
#include <math.h>
#include "lu5_math.h"

int beginShape(lua_State *L) 
{
	int shape_type = lu5_assert_integer(L, 1, "beginShape");

	LU5_APPLY_COLOR(lu5.style.fill);
	glBegin(shape_type);

	return 0;
}

int vertex(lua_State *L) 
{
	double x = lu5_assert_number(L, 1, "vertex");
	double y = lu5_assert_number(L, 2, "vertex");

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
	double x = lu5_assert_number(L, 1, "circle");  
	double y = lu5_assert_number(L, 2, "circle");
	double d = lu5_assert_number(L, 3, "circle");

	float radius = d / 2.0f;
	float angleStep = LU5_TWO_PI / LU5_CIRCLE_SEGMENTS;

	LU5_APPLY_COLOR(lu5.style.fill);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // Center of the circle
	
	for (int i = 0; i <= LU5_CIRCLE_SEGMENTS; i++) {
		float angle = angleStep * i;
		float x_offset = radius * cos(angle);
		float y_offset = radius * sin(angle);
		glVertex2f(x + x_offset, y + y_offset);
	}

	glEnd();

	LU5_APPLY_COLOR(lu5.style.stroke);

	glBegin(GL_LINE_LOOP);
		for (int i = 0; i <= LU5_CIRCLE_SEGMENTS; i++) {
			float angle = angleStep * i;
			float x_offset = radius * cos(angle);
			float y_offset = radius * sin(angle);

			glVertex2f(x + x_offset, y + y_offset);
		}
	glEnd();

	return 0;
}

int square(lua_State *L)
{
	double x = lu5_assert_number(L, 1, "square");
	double y = lu5_assert_number(L, 2, "square");  
	double s = lu5_assert_number(L, 3, "square");  

	float x2 = x + s;
	float y2 = y + s;

	LU5_APPLY_COLOR_IF_DIFFERENT(lu5.style.fill, lu5.style.stroke);

	glBegin(GL_QUADS);
		glVertex2f(x, y);
		glVertex2f(x2, y);
		glVertex2f(x2, y2);
		glVertex2f(x, y2);
	glEnd(); 

	return 0;
}

int rect(lua_State *L) 
{
	double x = lu5_assert_number(L, 1, "rect");  
	double y = lu5_assert_number(L, 2, "rect");  
	double w = lu5_assert_number(L, 3, "rect");  

	double h = w;
	if (lua_gettop(L) > 3) {
		h = lu5_assert_number(L, 4, "rect");
	}  

	float x2 = x + w;
	float y2 = y + h;

	LU5_APPLY_COLOR_IF_DIFFERENT(lu5.style.fill, lu5.style.stroke);

	glBegin(GL_QUADS);
		glVertex2f(x, y);
		glVertex2f(x2, y);
		glVertex2f(x2, y2);
		glVertex2f(x, y2);
	glEnd(); 

	return 0;
}

int line(lua_State *L) 
{
	double x1 = lu5_assert_number(L, 1, "line");
	double y1 = lu5_assert_number(L, 2, "line");
	double x2 = lu5_assert_number(L, 3, "line");
	double y2 = lu5_assert_number(L, 4, "line");

	float dx = x2 - x1;
	float dy = y2 - y1;
	float length = sqrt(dx * dx + dy * dy);

	float ux = ((float)lu5.style.strokeWeight / 2) * (dy / length);
	float uy = ((float)lu5.style.strokeWeight / 2) * (-dx / length);

	LU5_APPLY_COLOR_IF_DIFFERENT(lu5.style.stroke, lu5.style.fill);

	glBegin(GL_QUADS);
		glVertex2f(x1 - ux, y1 - uy);
		glVertex2f(x1 + ux, y1 + uy);
		glVertex2f(x2 + ux, y2 + uy);
		glVertex2f(x2 - ux, y2 - uy);
	glEnd();

	// Draw rounded circles
	if (lu5.style.strokeWeight < 3) return 0;

	float radius = ((float)lu5.style.strokeWeight) / 2.0f;

	float angleStep = (2 * LU5_PI) / LINE_POINT_SEGMENTS;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);
	for (int i = 0; i <= LINE_POINT_SEGMENTS; i++) {
		float angle = i * angleStep;
		float x = x1 + cos(angle) * radius;
		float y = y1 + sin(angle) * radius;
		glVertex2f(x, y);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x2, y2);
	for (int i = 0; i <= LINE_POINT_SEGMENTS; i++) {
		float angle = i * angleStep;
		float x = x2 + cos(angle) * radius;
		float y = y2 + sin(angle) * radius;
		glVertex2f(x, y);
	}
	glEnd();


	return 0;
}
int quad(lua_State *L)
{
	int argc;
	if ((argc = lua_gettop(L)) != 8) {
		luaL_error(L, "Expected 8 arguments got %i instead", argc);
		return 0;
	}

	double x1 = lu5_assert_number(L, 1, "quad");
	double y1 = lu5_assert_number(L, 2, "quad");
	double x2 = lu5_assert_number(L, 3, "quad");
	double y2 = lu5_assert_number(L, 4, "quad");
	double x3 = lu5_assert_number(L, 5, "quad");
	double y3 = lu5_assert_number(L, 6, "quad");
	double x4 = lu5_assert_number(L, 7, "quad");
	double y4 = lu5_assert_number(L, 8, "quad");

	LU5_APPLY_COLOR_IF_DIFFERENT(lu5.style.fill, lu5.style.stroke);

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
	double x = lu5_assert_number(L, 1, "point");
	double y = lu5_assert_number(L, 2, "point");

	// refer to https://p5js.org/reference/#/p5/point

	luaL_error(L, "TODO: Implement point.\t point(%f, %f);", x, y);
	return 0;
}

int triangle(lua_State *L)
{
	double x1 = lu5_assert_number(L, 1, "triangle");
	double y1 = lu5_assert_number(L, 2, "triangle");
	// ... more arguments
	// refer to https://p5js.org/reference/#/p5/triangle

	luaL_error(L, "TODO: Implement triangle.\t triangle(%f, %f, ...more args);", x1, y1);
	return 0;
}

int ellipse(lua_State *L)
{
	double x = lu5_assert_number(L, 1, "ellipse");
	double y = lu5_assert_number(L, 2, "ellipse");
	// ... more arguments
	// refer to https://p5js.org/reference/#/p5/ellipse

	luaL_error(L, "TODO: Implement ellipse.\t ellipse(%f, %f, ...more args);", x, y);
	return 0;
}


int arc(lua_State *L)
{
	double x = lu5_assert_number(L, 1, "arc");
	double y = lu5_assert_number(L, 2, "arc");
	// ... more arguments
	// refer to https://p5js.org/reference/#/p5/arc

	luaL_error(L, "TODO: Implement arc.\t arc(%f, %f, ...more args);", x, y);
	return 0;
}
