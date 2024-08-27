#include "../lu5_geometry.h"
#include <GL/gl.h>

#include "../../bindings/lu5_math.h"

#define LU5_CIRCLE_RES 10.8f

static int compute_segments(float w, float h)
{
	return (int)ceilf(LU5_CIRCLE_RES * (w + h));
} 

void lu5_render_ellipse(
	float x, float y, 
	float w, float h, 
	int segments) 
{
    float step = LU5_TWO_PI / segments;

    glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	
	for (int i = 0; i <= segments; i++) 
	{
		float angle = step * i;
		float px = w * cos(angle);
		float py = h * sin(angle);
		glVertex2f(x + px, y + py);
	}

	glEnd();
}