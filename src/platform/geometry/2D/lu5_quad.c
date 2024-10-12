#include "../../../lu5_geometry.h"
#include "../../../lu5_state.h"

static void lu5_render_quad_fill(
    lua_Number x1, lua_Number y1,
    lua_Number x2, lua_Number y2,
    lua_Number x3, lua_Number y3,
    lua_Number x4, lua_Number y4,
    lu5_color color)
{
	lu5_apply_color(color);

    glBegin(GL_QUADS);
		lu5_glVertex2(x1, y1);
		lu5_glVertex2(x2, y2);
		lu5_glVertex2(x3, y3);
		lu5_glVertex2(x4, y4);
	glEnd();
}

static void lu5_render_quad_stroke(
    lua_Number x1, lua_Number y1,
    lua_Number x2, lua_Number y2,
    lua_Number x3, lua_Number y3,
    lua_Number x4, lua_Number y4,
    lua_Number strokeWeight,
    lu5_color color)
{
	lu5_apply_color(color);

    glBegin(GL_TRIANGLE_STRIP);
    lu5_glVertex2(x1, y1);
    lu5_glVertex2(x1 - strokeWeight,  y1 - strokeWeight);
    
    lu5_glVertex2(x2, y2);
    lu5_glVertex2(x2 + strokeWeight,  y2 - strokeWeight);
    
    lu5_glVertex2(x3, y3);
    lu5_glVertex2(x3 + strokeWeight, y3 + strokeWeight);
    
    lu5_glVertex2(x4, y4);
    lu5_glVertex2(x4 - strokeWeight, y4 + strokeWeight);
    
    lu5_glVertex2(x1, y1);
    lu5_glVertex2(x1 - strokeWeight, y1 - strokeWeight);
    glEnd(); 
}

void lu5_render_quad(
    lua_Number x1, lua_Number y1,
    lua_Number x2, lua_Number y2,
    lua_Number x3, lua_Number y3,
    lua_Number x4, lua_Number y4,
    lua_Number strokeWeight,
    lu5_color fill,
    lu5_color stroke)
{
	if (lu5_color_visible(fill)) 
	{
		lu5_render_quad_fill(
			x1, y1, x2, y2, 
			x3, y3, x4, y4, 
			fill);
	}

	if (lu5_color_visible(stroke)) 
	{
		lu5_render_quad_stroke(
			x1, y1, x2, y2, 
			x3, y3, x4, y4,
			strokeWeight, 
			stroke);
	}

}