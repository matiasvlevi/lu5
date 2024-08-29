#ifndef _LU5_GEOMETRY_
#define _LU5_GEOMETRY_

#include <lua.h>
#include <GL/gl.h>
#include "../lu5_window.h"

#define LU5_CIRCLE_SEGMENTS 32

#define lu5_2D_over_3D_begin(depth_mode, width, height)\
    if (depth_mode == LU5_GL3D) {\
        glPushMatrix();glMatrixMode(GL_PROJECTION);\
        glPushMatrix();glLoadIdentity();\
        glOrtho(0.0, width, height, 0.0, -1.0, 10.0);\
        glMatrixMode(GL_MODELVIEW);glLoadIdentity();\
        glDisable(GL_CULL_FACE);glClear(GL_DEPTH_BUFFER_BIT);\
    }

#define lu5_2D_over_3D_end(depth_mode)\
    if (depth_mode == LU5_GL3D) {\
        glMatrixMode(GL_PROJECTION);glPopMatrix();\
        glMatrixMode(GL_MODELVIEW);glPopMatrix();\
    }

#if LUA_FLOAT_TYPE == LUA_FLOAT_FLOAT

#define lu5_glVertex2(x, y) glVertex2f((GLfloat)x, (GLfloat)y)
#define lu5_glVertex3(x, y, z) glVertex3f((GLfloat)x, (GLfloat)y, (GLfloat)z)
#define lu5_glNormal3(n1, n2, n3) glNormal3f((GLfloat)n1, (GLfloat)n2, (GLfloat)n3)
#define lu5_glTexCoord2(s, t)  glTexCoord2f((GLfloat)s, (GLfloat)t)
#define lu5_glTranslate(x, y, z)  glTranslatef((GLfloat)x, (GLfloat)y, (GLfloat)z)
#define lu5_glScale(x, y, z) glScalef((GLfloat)x, (GLfloat)y, (GLfloat)z)

#elif LUA_FLOAT_TYPE == LUA_FLOAT_DOUBLE

#define lu5_glVertex2(x, y) glVertex2d((GLdouble)x, (GLdouble)y)
#define lu5_glVertex3(x, y, z) glVertex3d((GLdouble)x, (GLdouble)y, (GLdouble)z)
#define lu5_glNormal3(n1, n2, n3) glNormal3d((GLdouble)n1, (GLdouble)n2, (GLdouble)n3)
#define lu5_glTexCoord2(s, t)  glTexCoord2d((GLdouble)s, (GLdouble)t)
#define lu5_glTranslate(x, y, z)  glTranslated((GLdouble)x, (GLdouble)y, (GLdouble)z)
#define lu5_glScale(x, y, z) glScaled((GLdouble)x, (GLdouble)y, (GLdouble)z)

#endif

// 2D
void lu5_render_ellipse(
    lua_Number x, lua_Number y, 
    lua_Number w, lua_Number h, 
    lua_Integer segments);

void lu5_render_ring(
    lua_Number x, lua_Number y, 
    lua_Number w, lua_Number h, 
    lua_Number strokeWeight, 
    lua_Integer segments);

void lu5_render_arc_fill(
    lua_Number x, lua_Number y, 
    lua_Number w, lua_Number h, 
    lua_Number start_angle, 
    lua_Number end_angle, 
    lua_Integer segments);

void lu5_render_arc_stroke(
    lua_Number x, lua_Number y, 
    lua_Number w, lua_Number h, 
    lua_Number strokeWeight,
    lua_Number start_angle, 
    lua_Number end_angle, 
    lua_Integer segments);
    
void lu5_render_quad_fill(
    lua_Number x1, lua_Number y1,
    lua_Number x2, lua_Number y2,
    lua_Number x3, lua_Number y3,
    lua_Number x4, lua_Number y4);

void lu5_render_quad_stroke(
    lua_Number x1, lua_Number y1,
    lua_Number x2, lua_Number y2,
    lua_Number x3, lua_Number y3,
    lua_Number x4, lua_Number y4,
    lua_Number strokeWeight);

// 3D
void lu5_render_debug();

void lu5_render_plane_edges(lua_Number half_x, lua_Number half_y);
void lu5_render_plane_faces(lua_Number half_x, lua_Number half_y);

void lu5_render_ellipsoid_faces(lua_Number radius, lua_Integer detail_x, lua_Integer detail_y);
void lu5_render_ellipsoid_edges(lua_Number radius, lua_Integer detail_x, lua_Integer detail_y);

void lu5_render_box_faces(lua_Number width, lua_Number height, lua_Number depth);
void lu5_render_box_edges(lua_Number width, lua_Number height, lua_Number depth);


#endif
