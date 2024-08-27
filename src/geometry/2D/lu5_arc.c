#include "../lu5_geometry.h"
#include <GL/gl.h>

#include "../../bindings/lu5_math.h"
#include "../../lu5_state.h"


void lu5_render_arc_stroke(
	float x, float y, 
	float w, float h, 
	float ow, float oh, 
	float start_angle, 
	float end_angle, 
	int segments)
{
	float step = LU5_TWO_PI / (segments * 8.0f);

	glBegin(GL_TRIANGLE_STRIP);
	for (float angle = start_angle; angle <= end_angle; angle += step) 
	{
		float px = cos(angle);
		float py = sin(angle);

        glVertex2f(px * ow + x, py * oh + y);
		glVertex2f(px * w + x, py * h + y);
	}
	glEnd();
}

void lu5_render_arc_fill(
	float x, float y, 
	float w, float h, 
	float start_angle, 
	float end_angle, 
	int segments)
{
	float step = LU5_TWO_PI / (segments * 8.0f);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (float angle = start_angle; angle < end_angle; angle += step) 
	{
		float px = w * cos(angle);
		float py = h * sin(angle);

		glVertex2f(x + px, y + py);
	}
	glEnd();
}
