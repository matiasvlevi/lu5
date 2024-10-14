#include "../../../lu5_geometry.h"
#include "../../../lu5_setting.h"

#include "../../../lu5_state.h"

#include <math.h>

static void lu5_render_triangle_fill(
    lua_Number x1, lua_Number y1,
    lua_Number x2, lua_Number y2,
    lua_Number x3, lua_Number y3,
    lu5_color color)
{
    lu5_glBegin(GL_TRIANGLES, color);
        lu5_glVertex2(x1, y1);
        lu5_glVertex2(x2, y2);
        lu5_glVertex2(x3, y3);
    lu5_glEnd();
}

static void lu5_render_stroke(float x1, float y1, float x2, float y2, float thickness) {
    float dx, dy, len, nx, ny;

    dx = x2 - x1;
    dy = y2 - y1;
    len = sqrtf(dx * dx + dy * dy);
    nx = -dy / len * thickness / 2;
    ny = dx / len * thickness / 2;

    glBegin(GL_TRIANGLES);
        glVertex2f(x1 - nx, y1 - ny);
        glVertex2f(x2 - nx, y2 - ny);
        glVertex2f(x2 + nx, y2 + ny);

        glVertex2f(x1 - nx, y1 - ny);
        glVertex2f(x2 + nx, y2 + ny);
        glVertex2f(x1 + nx, y1 + ny);
    glEnd();
}

static void lu5_render_triangle_stroke(float x1, float y1, float x2, float y2, float x3, float y3, float strokeWeight, lu5_color color) 
{
    lu5_apply_color(color);

    lu5_render_stroke(x1, y1, x2, y2, strokeWeight);
    lu5_render_stroke(x2, y2, x3, y3, strokeWeight);
    lu5_render_stroke(x3, y3, x1, y1, strokeWeight);

    lua_Number radius = strokeWeight / 2;

    lu5_render_ellipse_fill(x1, y1, radius, radius, color, LU5_CIRCLE_SEGMENTS);
    lu5_render_ellipse_fill(x2, y2, radius, radius, color, LU5_CIRCLE_SEGMENTS);
    lu5_render_ellipse_fill(x3, y3, radius, radius, color, LU5_CIRCLE_SEGMENTS);
}


void lu5_render_triangle(
    lua_Number x1, lua_Number y1,
    lua_Number x2, lua_Number y2,
    lua_Number x3, lua_Number y3,
    lua_Integer strokeWeight,
    lu5_color fill,
    lu5_color stroke)
{
	lu5_2D_over_3D_begin(lu5.depth_mode, lu5.width, lu5.height);

	if (lu5_has_fill())
	{
		lu5_render_triangle_fill(x1, y1, x2, y2, x3, y3, lu5_style(&lu5)->fill);
	}

	if (lu5_has_stroke()) 
	{
		lu5_render_triangle_stroke(x1, y1, x2, y2, x3, y3, lu5_style(&lu5)->strokeWeight, lu5_style(&lu5)->stroke);
	}

	lu5_2D_over_3D_end(lu5.depth_mode);
}