#include "../../../lu5_geometry.h"
#include "../../../bindings/lu5_math.h"
#include "../../../lu5_state.h"
#include "../../../lu5_logger.h"
#define LU5_CIRCLE_RES 10.8f

static void lu5_render_ring(
	lua_Number x, lua_Number y,
	lua_Number inner_radius_w, lua_Number inner_radius_h,
	lua_Number strokeWeight,
	lu5_color color, 
	lua_Integer segments)
{
	lu5_apply_color(color);
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

void lu5_render_ellipse(
	lua_Number x, lua_Number y, 
	lua_Number w, lua_Number h,
	lu5_color color, 
	lua_Integer segments) 
{
	lu5_apply_color(color);

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

void lu5_render_ellipse_w_stroke(
    lua_Number x, lua_Number y,
    lua_Number w, lua_Number h,
    lua_Number strokeWeight,
    lu5_color fill,
    lu5_color stroke,
    lua_Integer segments)
{
	if (lu5_color_visible(stroke)) 
	{
		lu5_render_ring(x, y, w, h, 
			strokeWeight, stroke, 
			LU5_CIRCLE_SEGMENTS);
	}

	if (lu5_color_visible(fill))
	{
		lu5_render_ellipse(x, y, w, h, 
			fill,			
			LU5_CIRCLE_SEGMENTS);
	}
}