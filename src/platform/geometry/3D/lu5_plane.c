#include "../../../lu5_geometry.h"
#include <GL/gl.h>

void lu5_render_plane_edges(lua_Number half_x, lua_Number half_y, lu5_color color)
{
	lu5_apply_color(color);
    glBegin(GL_LINE_LOOP);
        lu5_glVertex3(-half_x, -half_y, 0.0f);
        lu5_glVertex3( half_x, -half_y, 0.0f);
        lu5_glVertex3( half_x,  half_y, 0.0f);
        lu5_glVertex3(-half_x,  half_y, 0.0f);
        lu5_glVertex3( half_x, -half_y, 0.0f);
        lu5_glVertex3(-half_x,  half_y, 0.0f);
    glEnd();
}

void lu5_render_plane_faces(lua_Number half_x, lua_Number half_y, lu5_color color)
{
	lu5_apply_color(color);
    glBegin(GL_QUADS);
        lu5_glVertex3(-half_x, -half_y, 0.0f);
        lu5_glVertex3( half_x, -half_y, 0.0f);
        lu5_glVertex3( half_x,  half_y, 0.0f);
        lu5_glVertex3(-half_x,  half_y, 0.0f);
    glEnd();
}