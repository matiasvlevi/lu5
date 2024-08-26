#include "lu5_geometry.h"
#include <GL/gl.h>
#include "../bindings/lu5_math.h"

void lu5_render_ellipse(float x, float y, float w, float h, int segments) 
{
    glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);

    static float step = LU5_TWO_PI / LU5_CIRCLE_SEGMENTS;
	
	for (int i = 0; i <= segments; i++) {
		float angle = step * i;
		float px = w * cos(angle);
		float py = h * sin(angle);
		glVertex2f(x + px, y + py);
	}

	glEnd();
}