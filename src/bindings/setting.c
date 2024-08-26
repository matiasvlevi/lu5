#include "setting.h"

#include <lauxlib.h>

#include "window.h"

#include "../lu5_state.h"
#include "../lu5_font.h"
#include "../lu5_types.h"

int background(lua_State *L) 
{
	lu5_color color = lu5_args_to_color(L);

	glClearColor(
		((GLfloat)color.r)/255.0f, 
		((GLfloat)color.g)/255.0f, 
		((GLfloat)color.b)/255.0f, 
		((GLfloat)color.a)/255.0f
	);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();

	if (lu5.depth_mode == LU5_GL3D) {
		glTranslatef(0.0f, 0.0f, -800.0f);
		glScalef(-1, 1, 1);
	}

	return 0;
}

int strokeWeight(lua_State *L) 
{
	lua_Number weight = lu5_assert_number(L, 1, "strokeWeight");
	
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

int push(lua_State *L) 
{
	lu5.style_cache = lu5.style;
	LU5_SET_DEFAULT_STYLE(&lu5.style);
	glPushMatrix();
	return 0;
}

int pop(lua_State *L) 
{
	lu5.style = lu5.style_cache;
	LU5_SET_DEFAULT_STYLE(&lu5.style_cache);
	glPopMatrix();
	return 0;
}
