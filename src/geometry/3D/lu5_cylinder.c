#include "../lu5_geometry.h"
#include <math.h>

void lu5_render_cylinder_faces(
    lua_Number radius, lua_Number height, 
    lua_Integer detailX, lua_Integer detailY, 
    bool bottom_cap, 
    bool top_cap) 
{
    lua_Number halfHeight = height / 2.0;

    for (lua_Integer i = 0; i < detailY; i++) {
        lua_Number y0 = -halfHeight + (height * i / (lua_Number)detailY);
        lua_Number y1 = -halfHeight + (height * (i + 1) / (lua_Number)detailY);

        glBegin(GL_QUAD_STRIP);
        for (lua_Integer j = 0; j <= detailX; j++) {
            lua_Number theta = 2 * M_PI * j / (lua_Number)detailX;
            lua_Number cosTheta = cosf(theta);
            lua_Number sinTheta = sinf(theta);

            lua_Number x = cosTheta * radius;
            lua_Number z = sinTheta * radius;

            lu5_glVertex3(x, y0, z);
            lu5_glVertex3(x, y1, z);
        }
        glEnd();
    }

    if (bottom_cap) 
    {
        glBegin(GL_TRIANGLE_FAN);
        lu5_glVertex3(0.0, -halfHeight, 0.0);
        for (lua_Integer j = 0; j <= detailX; j++) {
            lua_Number theta = 2 * M_PI * j / (lua_Number)detailX;
            lua_Number cosTheta = cosf(theta);
            lua_Number sinTheta = sinf(theta);

            lua_Number x = cosTheta * radius;
            lua_Number z = sinTheta * radius;

            lu5_glVertex3(x, -halfHeight, z);
        }
        glEnd();
    }

    if (top_cap) 
    {
        glBegin(GL_TRIANGLE_FAN);
        lu5_glVertex3(0.0, halfHeight, 0.0);
        for (lua_Integer j = 0; j <= detailX; j++) {
            lua_Number theta = 2 * M_PI * j / (lua_Number)detailX;
            lua_Number cosTheta = cosf(theta);
            lua_Number sinTheta = sinf(theta);

            lua_Number x = cosTheta * radius;
            lua_Number z = sinTheta * radius;

            lu5_glVertex3(x, halfHeight, z);
        }
        glEnd();
    }
}

void lu5_render_cylinder_edges(
    lua_Number radius, lua_Number height, 
    lua_Integer detail_x, lua_Integer detail_y, 
    bool bottom_cap, 
    bool top_cap) 
{
    lua_Number half_height = height / 2.0;

    for (lua_Integer j = 0; j <= detail_x; j++) {
        lua_Number theta = 2 * M_PI * j / (lua_Number)detail_x;
        lua_Number cos_theta = cosf(theta);
        lua_Number sin_theta = sinf(theta);

        lua_Number x = cos_theta * radius;
        lua_Number z = sin_theta * radius;

        glBegin(GL_LINE_STRIP);
        for (lua_Integer i = 0; i <= detail_y; i++) {
            lua_Number y = -half_height + (height * i / (lua_Number)detail_y);
            lu5_glVertex3(x, y, z);
        }
        glEnd();
    }

    for (lua_Integer i = 0; i <= detail_y; i++) {
        lua_Number y = -half_height + (height * i / (lua_Number)detail_y);

        glBegin(GL_LINE_STRIP);
        for (lua_Integer j = 0; j <= detail_x; j++) {
            lua_Number theta = 2 * M_PI * j / (lua_Number)detail_x;
            lua_Number cos_theta = cosf(theta);
            lua_Number sin_theta = sinf(theta);

            lua_Number x = cos_theta * radius;
            lua_Number z = sin_theta * radius;

            lu5_glVertex3(x, y, z);
        }
        glEnd();
    }

    if (bottom_cap) 
    {
        glBegin(GL_LINE_LOOP);
        for (lua_Integer j = 0; j < detail_x; j++) {
            lua_Number theta = 2 * M_PI * j / (lua_Number)detail_x;
            lua_Number cos_theta = cosf(theta);
            lua_Number sin_theta = sinf(theta);

            lua_Number x = cos_theta * radius;
            lua_Number z = sin_theta * radius;

            lu5_glVertex3(x, -half_height, z);
        }
        glEnd();
    }

    if (top_cap) 
    {
        glBegin(GL_LINE_LOOP);
        for (lua_Integer j = 0; j < detail_x; j++) {
            lua_Number theta = 2 * M_PI * j / (lua_Number)detail_x;
            lua_Number cos_theta = cosf(theta);
            lua_Number sin_theta = sinf(theta);

            lua_Number x = cos_theta * radius;
            lua_Number z = sin_theta * radius;

            lu5_glVertex3(x, half_height, z);
        }
        glEnd();
    }
}