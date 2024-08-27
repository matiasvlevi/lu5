#include "../lu5_geometry.h"
#include <GL/gl.h>

#include "../../bindings/lu5_math.h"
#include "../../lu5_logger.h"

void lu5_render_ring(
	float x, float y, 
	float inner_radius, 
	float outer_radius, 
	int segments)
{
	float step = LU5_TWO_PI / segments;

	glBegin(GL_TRIANGLE_STRIP);

	float angle = 0.0f;
	for (int i = 0; i <= segments; ++i) 
	{
		angle = i * step;
		float px = cos(angle);
		float py = sin(angle);

		glVertex2f(px * outer_radius + x, py * outer_radius + y);
		glVertex2f(px * inner_radius + x, py * inner_radius + y);
	}
	glEnd();
}