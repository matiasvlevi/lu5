#include "../../../lu5_geometry.h"
#include "../../../bindings/lu5_math.h"
#include "../../../lu5_state.h"

static void lu5_render_arc_stroke(
	lua_Number x, lua_Number y, 
	lua_Number w, lua_Number h, 
	lua_Number strokeWeight,
	lua_Number start_angle, 
	lua_Number end_angle, 
	lua_Integer segments,
	lu5_color color)
{
	lu5_apply_color(color);

	lua_Number step = LU5_TWO_PI / (segments * 8.0f);

	float outer_radius_w = w + strokeWeight;
	float outer_radius_h = h + strokeWeight;

	glBegin(GL_TRIANGLE_STRIP);
	for (lua_Number angle = start_angle; angle <= end_angle; angle += step) 
	{
		lua_Number px = cos(angle);
		lua_Number py = sin(angle);

        lu5_glVertex2(px * outer_radius_w + x, py * outer_radius_h + y);
		lu5_glVertex2(px * w + x, py * h + y);
	}
	glEnd();
}

static void lu5_render_arc_fill(
	lua_Number x, lua_Number y, 
	lua_Number w, lua_Number h, 
	lua_Number start_angle, 
	lua_Number end_angle, 
	lua_Integer segments,
	lu5_color color)
{
	lu5_apply_color(color);

	lua_Number step = LU5_TWO_PI / (segments * 8.0f);

	glBegin(GL_TRIANGLE_FAN);
	lu5_glVertex2(x, y);
	for (lua_Number angle = start_angle; angle < end_angle; angle += step) 
	{
		lua_Number px = w * cos(angle);
		lua_Number py = h * sin(angle);

		lu5_glVertex2(x + px, y + py);
	}
	glEnd();
}

void lu5_render_arc(    
	lua_Number x, lua_Number y, 
    lua_Number w, lua_Number h, 
    lua_Number strokeWeight,
    lua_Number start_angle, 
    lua_Number end_angle, 
    lua_Integer segments,
    lu5_color fill,
    lu5_color stroke)
{
	lu5_2D_over_3D_begin(lu5.depth_mode, lu5.width, lu5.height);
	if (lu5_has_fill())
	{
		lu5_render_arc_fill(
			x, y, 
			w, h, 
			start_angle, end_angle,
			LU5_CIRCLE_SEGMENTS,
			fill);
	}

	if (lu5_has_stroke())
	{
		lu5_glLineWidth(strokeWeight);
		lu5_render_arc_stroke(
			x, y, 
			w, h, 
			strokeWeight,
			start_angle, end_angle, 
			LU5_CIRCLE_SEGMENTS,
			stroke);
	}
	lu5_2D_over_3D_end(lu5.depth_mode);

}