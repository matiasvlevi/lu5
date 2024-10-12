#ifndef __LU5_GEOMETRY_CORE_H__
#define __LU5_GEOMETRY_CORE_H__

#ifndef LU5_WASM
#include <GL/gl.h>
#endif

#include <stdbool.h>

#define LU5_CIRCLE_SEGMENTS 32
#define LINE_POINT_SEGMENTS 24

#ifndef LU5_WASM
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
        #define lu5_glLineWidth(w) glLineWidth((GLfloat)w)
        #define lu5_glRotate(angle, x, y, z) glRotatef((GLfloat)angle, (GLfloat)x, (GLfloat)y, (GLfloat)z)

    #elif LUA_FLOAT_TYPE == LUA_FLOAT_DOUBLE

        #define lu5_glVertex2(x, y) glVertex2d((GLdouble)x, (GLdouble)y)
        #define lu5_glVertex3(x, y, z) glVertex3d((GLdouble)x, (GLdouble)y, (GLdouble)z)
        #define lu5_glNormal3(n1, n2, n3) glNormal3d((GLdouble)n1, (GLdouble)n2, (GLdouble)n3)
        #define lu5_glTexCoord2(s, t)  glTexCoord2d((GLdouble)s, (GLdouble)t)
        #define lu5_glTranslate(x, y, z)  glTranslated((GLdouble)x, (GLdouble)y, (GLdouble)z)
        #define lu5_glScale(x, y, z) glScaled((GLdouble)x, (GLdouble)y, (GLdouble)z)
        #define lu5_glLineWidth(w) glLineWidth((GLdouble)w)
        #define lu5_glRotate(angle, x, y, z) glRotated((GLdouble)angle, (GLdouble)x, (GLdouble)y, (GLdouble)z)

    #endif

#else // LU5_WASM

    // Ignored functions in wasm
    #define lu5_2D_over_3D_begin(depth_mode, width, height) ("")
    #define lu5_2D_over_3D_end(depth_mode) ("")
    #define lu5_glLineWidth(w) ("")
    #define lu5_glVertex3(x, y, z) ("")
    #define lu5_glNormal3(n1, n2, n3) ("")
    #define lu5_glTexCoord2(s, t) ("")

    // TODO: Implement transform matrix in wasm
    #define lu5_glTranslate(x, y, z) ("")
    #define lu5_glScale(x, y, z) ("")
    #define lu5_glRotate(angle, x, y, z) ("")

	#define GL_POINTS 0
	#define GL_QUADS 1
	#define GL_LINES 2
	#define GL_LINE_STRIP 3
	#define GL_LINE_LOOP 4
	#define GL_TRIANGLES 5
	#define GL_TRIANGLE_STRIP 6
	#define GL_TRIANGLE_FAN 7
	#define GL_QUAD_STRIP 8

#endif


#endif