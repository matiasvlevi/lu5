#include "shapes.h"

#include "../lu5_state.h"
#include "../lu5_font.h"
#include "../lu5_image.h"

#include <lauxlib.h>
#include <math.h>
#include "lu5_math.h"

int beginShape(lua_State *L) 
{
	int shape_type = lua_tointeger(L, 1);

	LU5_APPLY_COLOR(lu5.style.fill);
	glBegin(shape_type);

	return 0;
}

int vertex(lua_State *L) 
{
	double x = lua_tonumber(L, 1);
	double y = lua_tonumber(L, 2);

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
	double x = lua_tonumber(L, 1);  
	double y = lua_tonumber(L, 2);  
	double d = lua_tonumber(L, 3);  

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
	double x = lua_tonumber(L, 1);  
	double y = lua_tonumber(L, 2);  
	double s = lua_tonumber(L, 3);  

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
	double x = lua_tonumber(L, 1);  
	double y = lua_tonumber(L, 2);  
	double w = lua_tonumber(L, 3);  

	double h = w;
	if (lua_gettop(L) > 3) {
		h = lua_tonumber(L, 4);
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
	double x1 = lua_tonumber(L, 1);
	double y1 = lua_tonumber(L, 2);
	double x2 = lua_tonumber(L, 3);
	double y2 = lua_tonumber(L, 4);

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

	double x1 = lua_tonumber(L, 1);
	double y1 = lua_tonumber(L, 2);
	double x2 = lua_tonumber(L, 3);
	double y2 = lua_tonumber(L, 4);
	double x3 = lua_tonumber(L, 5);
	double y3 = lua_tonumber(L, 6);
	double x4 = lua_tonumber(L, 7);
	double y4 = lua_tonumber(L, 8);

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
	double x = lua_tonumber(L, 1);
	double y = lua_tonumber(L, 2);

	// refer to https://p5js.org/reference/#/p5/point

	luaL_error(L, "TODO: Implement point.\t point(%f, %f);", x, y);
	return 0;
}

int triangle(lua_State *L)
{
	double x1 = lua_tonumber(L, 1);
	double y1 = lua_tonumber(L, 2);
	// ... more arguments
	// refer to https://p5js.org/reference/#/p5/triangle

	luaL_error(L, "TODO: Implement triangle.\t triangle(%f, %f, ...more args);", x1, y1);
	return 0;
}

int ellipse(lua_State *L)
{
	double x = lua_tonumber(L, 1);
	double y = lua_tonumber(L, 2);
	// ... more arguments
	// refer to https://p5js.org/reference/#/p5/ellipse

	luaL_error(L, "TODO: Implement ellipse.\t ellipse(%f, %f, ...more args);", x, y);
	return 0;
}


int arc(lua_State *L)
{
	double x = lua_tonumber(L, 1);
	double y = lua_tonumber(L, 2);
	// ... more arguments
	// refer to https://p5js.org/reference/#/p5/arc

	luaL_error(L, "TODO: Implement arc.\t arc(%f, %f, ...more args);", x, y);
	return 0;
}
