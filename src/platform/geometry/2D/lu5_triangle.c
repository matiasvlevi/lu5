#include "../../../lu5_geometry.h"
#include "../../../lu5_setting.h"

void lu5_render_triangle_fill(
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


