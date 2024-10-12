#include "../lu5_setting.h"
#include "../lu5_state.h"

#include "../lu5_geometry.h"


#include <GLFW/glfw3.h>

void lu5_background(lu5_color color)
{
	glClearColor(
		(lua_Number)(color.r) / 255.0, 
		(lua_Number)(color.g) / 255.0, 
		(lua_Number)(color.b) / 255.0, 
		(lua_Number)(color.a) / 255.0
	);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();

	if (lu5.depth_mode == LU5_GL3D) {
		lu5_glTranslate(0.0f, 0.0f, -800.0f);
		glScalef(-1, 1, 1);
	}
}

void lu5_glBegin(int shape_type, lu5_color color)
{
	lu5_apply_color(color);
	glBegin(shape_type);
}

void lu5_glEnd()
{
	glEnd();
}