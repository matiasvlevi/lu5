#include "../../../lu5_geometry.h"
#include <math.h>

void lu5_render_torus_faces(
    lua_Number radius, lua_Number tubeRadius, 
    lua_Integer detailX, lua_Integer detailY,
    lu5_color color) 
{
    lu5_apply_color(color);
    for (lua_Integer i = 0; i < detailX; i++) {
        lua_Number theta = 2 * M_PI * i / (lua_Number)detailX;
        lua_Number nextTheta = 2 * M_PI * (i + 1) / (lua_Number)detailX;
        lua_Number cosTheta = cosf(theta);
        lua_Number sinTheta = sinf(theta);
        lua_Number cosNextTheta = cosf(nextTheta);
        lua_Number sinNextTheta = sinf(nextTheta);

        for (lua_Integer j = 0; j < detailY; j++) {
            lua_Number phi = 2 * M_PI * j / (lua_Number)detailY;
            lua_Number nextPhi = 2 * M_PI * (j + 1) / (lua_Number)detailY;
            lua_Number cosPhi = cosf(phi);
            lua_Number sinPhi = sinf(phi);
            lua_Number cosNextPhi = cosf(nextPhi);
            lua_Number sinNextPhi = sinf(nextPhi);

            lua_Number x1 = (radius + tubeRadius * cosPhi) * cosTheta;
            lua_Number y1 = (radius + tubeRadius * cosPhi) * sinTheta;
            lua_Number z1 = tubeRadius * sinPhi;

            lua_Number x2 = (radius + tubeRadius * cosNextPhi) * cosTheta;
            lua_Number y2 = (radius + tubeRadius * cosNextPhi) * sinTheta;
            lua_Number z2 = tubeRadius * sinNextPhi;

            lua_Number x3 = (radius + tubeRadius * cosPhi) * cosNextTheta;
            lua_Number y3 = (radius + tubeRadius * cosPhi) * sinNextTheta;
            lua_Number z3 = tubeRadius * sinPhi;

            lua_Number x4 = (radius + tubeRadius * cosNextPhi) * cosNextTheta;
            lua_Number y4 = (radius + tubeRadius * cosNextPhi) * sinNextTheta;
            lua_Number z4 = tubeRadius * sinNextPhi;

            glBegin(GL_TRIANGLES);

            // First triangle (x1, x2, x3)
            lu5_glVertex3(x1, y1, z1);
            lu5_glVertex3(x2, y2, z2);
            lu5_glVertex3(x3, y3, z3);

            // Second triangle (x2, x3, x4)
            lu5_glVertex3(x2, y2, z2);
            lu5_glVertex3(x3, y3, z3);
            lu5_glVertex3(x4, y4, z4);

            glEnd();
        }
    }
}

void lu5_render_torus_edges(
    lua_Number radius, 
    lua_Number tubeRadius, 
    lua_Integer detailX, 
    lua_Integer detailY,
    lu5_color color) 
{
    lu5_apply_color(color);
    for (lua_Integer i = 0; i < detailX; i++) {
        lua_Number theta = 2 * M_PI * i / (lua_Number)detailX;
        lua_Number nextTheta = 2 * M_PI * (i + 1) / (lua_Number)detailX;
        lua_Number cosTheta = cosf(theta);
        lua_Number sinTheta = sinf(theta);
        lua_Number cosNextTheta = cosf(nextTheta);
        lua_Number sinNextTheta = sinf(nextTheta);
        
        glBegin(GL_LINES);
        for (lua_Integer j = 0; j < detailY; j++) {
            lua_Number phi = 2 * M_PI * j / (lua_Number)detailY;
            lua_Number nextPhi = 2 * M_PI * (j + 1) / (lua_Number)detailY;
            lua_Number cosPhi = cosf(phi);
            lua_Number sinPhi = sinf(phi);
            lua_Number cosNextPhi = cosf(nextPhi);
            lua_Number sinNextPhi = sinf(nextPhi);
            
            lua_Number x1 = (radius + tubeRadius * cosPhi) * cosTheta;
            lua_Number y1 = (radius + tubeRadius * cosPhi) * sinTheta;
            lua_Number z1 = tubeRadius * sinPhi;
            
            lua_Number x2 = (radius + tubeRadius * cosNextPhi) * cosTheta;
            lua_Number y2 = (radius + tubeRadius * cosNextPhi) * sinTheta;
            lua_Number z2 = tubeRadius * sinNextPhi;
            
            lua_Number x3 = (radius + tubeRadius * cosPhi) * cosNextTheta;
            lua_Number y3 = (radius + tubeRadius * cosPhi) * sinNextTheta;
            lua_Number z3 = tubeRadius * sinPhi;
            
            // Draw vertical segments
            lu5_glVertex3(x1, y1, z1); lu5_glVertex3(x2, y2, z2);
            
            // Draw horizontal segments
            lu5_glVertex3(x1, y1, z1); lu5_glVertex3(x3, y3, z3);
            
            // Draw diagonal
            lu5_glVertex3(x2, y2, z2); lu5_glVertex3(x3, y3, z3);
        }
        glEnd();
    }
}