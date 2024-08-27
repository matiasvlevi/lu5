#include "../lu5_geometry.h"
#include <GL/gl.h>

void lu5_render_plane_edges(float half_x, float half_y)
{
    glBegin(GL_LINE_LOOP);
        glVertex3f(-half_x, -half_y, 0.0f);
        glVertex3f( half_x, -half_y, 0.0f);
        glVertex3f( half_x,  half_y, 0.0f);
        glVertex3f(-half_x,  half_y, 0.0f);
        glVertex3f( half_x, -half_y, 0.0f);
        glVertex3f(-half_x,  half_y, 0.0f);
    glEnd();
}

void lu5_render_plane_faces(float half_x, float half_y)
{
    glBegin(GL_QUADS);
        glVertex3f(-half_x, -half_y, 0.0f);
        glVertex3f( half_x, -half_y, 0.0f);
        glVertex3f( half_x,  half_y, 0.0f);
        glVertex3f(-half_x,  half_y, 0.0f);
    glEnd();
}