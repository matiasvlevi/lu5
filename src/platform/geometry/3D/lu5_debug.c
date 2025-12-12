#include "../../../lu5_geometry.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#define DEBUG_GRID_STEP 20.0f
#define DEBUG_HALF_GRID_PLANE 200.0f

void lu5_render_debug() 
{
	glPushMatrix();
    // Axes
	glPushMatrix();
        // X
		lu5_glTranslate(-DEBUG_HALF_GRID_PLANE - 1, -DEBUG_HALF_GRID_PLANE, -DEBUG_HALF_GRID_PLANE - 1);
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glLineWidth(6);
		glBegin(GL_LINES);
			lu5_glVertex3(0.0f, 0.0f, 0.0f);
			lu5_glVertex3(100.0f, 0.0f, 0.0f);
		glEnd();

        // Y
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		glLineWidth(6);
		glBegin(GL_LINES);
			lu5_glVertex3(0.0f, 0.0f, 0.0f);
			lu5_glVertex3(0.0f, 100.0f, 0.0f);
		glEnd();

        // Z
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		glLineWidth(6);
		glBegin(GL_LINES);
			lu5_glVertex3(0.0f, 0.0f, 0.0f);
			lu5_glVertex3(0.0f, 0.0f, 100.0f);
		glEnd();
	glPopMatrix();

    // Grid plane
	glPushMatrix();
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glLineWidth(2);
	glBegin(GL_LINES);
		for (lua_Number x = -DEBUG_HALF_GRID_PLANE; x < DEBUG_HALF_GRID_PLANE; x += DEBUG_GRID_STEP) {
			lu5_glVertex3(x, 0.0f, -DEBUG_HALF_GRID_PLANE);
			lu5_glVertex3(x, 0.0f, DEBUG_HALF_GRID_PLANE);
		}

		for (lua_Number y = -DEBUG_HALF_GRID_PLANE; y < DEBUG_HALF_GRID_PLANE; y += DEBUG_GRID_STEP) {
			lu5_glVertex3(-DEBUG_HALF_GRID_PLANE, 0.0f, y);
			lu5_glVertex3( DEBUG_HALF_GRID_PLANE, 0.0f, y);
		}

		lu5_glVertex3(DEBUG_HALF_GRID_PLANE, 0.0f,  DEBUG_HALF_GRID_PLANE);
		lu5_glVertex3(DEBUG_HALF_GRID_PLANE, 0.0f, -DEBUG_HALF_GRID_PLANE);

		lu5_glVertex3(DEBUG_HALF_GRID_PLANE,  0.0f, DEBUG_HALF_GRID_PLANE);
		lu5_glVertex3(-DEBUG_HALF_GRID_PLANE, 0.0f,  DEBUG_HALF_GRID_PLANE);
	glEnd();
	
	glPopMatrix();
	glPopMatrix();

}
