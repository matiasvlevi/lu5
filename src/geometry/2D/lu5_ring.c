#include "../lu5_geometry.h"
#include "../../bindings/lu5_math.h"
#include "../../lu5_logger.h"

void lu5_render_ring(
	lua_Number x, lua_Number y,
	lua_Number inner_radius_w, lua_Number inner_radius_h,
	lua_Number strokeWeight, 
	lua_Integer segments)
{
	lua_Number step = LU5_TWO_PI / segments;

	glBegin(GL_TRIANGLE_STRIP);

	float outer_radius_w = inner_radius_w + strokeWeight;
	float outer_radius_h = inner_radius_h + strokeWeight;

	lua_Number angle = 0.0f;
	for (lua_Integer i = 0; i <= segments; ++i) 
	{
		angle = i * step;
		lua_Number px = cos(angle);
		lua_Number py = sin(angle);

		lu5_glVertex2(px * (outer_radius_w) + x, py * (outer_radius_h) + y);
		lu5_glVertex2(px * (inner_radius_w) + x, py * (inner_radius_h) + y);
	}
	glEnd();
}