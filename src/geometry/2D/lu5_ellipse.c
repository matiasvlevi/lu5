#include "../lu5_geometry.h"
#include "../../bindings/lu5_math.h"

#define LU5_CIRCLE_RES 10.8f

void lu5_render_ellipse(
	lua_Number x, lua_Number y, 
	lua_Number w, lua_Number h, 
	lua_Integer segments) 
{
    lua_Number step = LU5_TWO_PI / segments;

    glBegin(GL_TRIANGLE_FAN);
	lu5_glVertex2(x, y);
	
	for (lua_Integer i = 0; i <= segments; i++) 
	{
		lua_Number angle = step * i;
		lua_Number px = w * cos(angle);
		lua_Number py = h * sin(angle);
		lu5_glVertex2(x + px, y + py);
	}

	glEnd();
}