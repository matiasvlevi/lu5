#include "../lu5_geometry.h"
#include <GL/gl.h>

#define DEBUG_GRID_STEP 20.0f
#define DEBUG_HALF_GRID_PLANE 200.0f

void lu5_render_debug() 
{	
    // Axes
	glPushMatrix();
        // X
		glTranslatef(-DEBUG_HALF_GRID_PLANE - 1, -DEBUG_HALF_GRID_PLANE, -DEBUG_HALF_GRID_PLANE - 1);
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glLineWidth(6);
		glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(100.0f, 0.0f, 0.0f);
		glEnd();

        // Y
		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		glLineWidth(6);
		glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 100.0f, 0.0f);
		glEnd();

        // Z
		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		glLineWidth(6);
		glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 100.0f);
		glEnd();
	glPopMatrix();

    // Grid plane
	glPushMatrix();
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glLineWidth(2);
	glBegin(GL_LINES);
		for (float x = -DEBUG_HALF_GRID_PLANE; x < DEBUG_HALF_GRID_PLANE; x += DEBUG_GRID_STEP) {
			glVertex3f(x, 0.0f, -DEBUG_HALF_GRID_PLANE);
			glVertex3f(x, 0.0f, DEBUG_HALF_GRID_PLANE);
		}

		for (float y = -DEBUG_HALF_GRID_PLANE; y < DEBUG_HALF_GRID_PLANE; y += DEBUG_GRID_STEP) {
			glVertex3f(-DEBUG_HALF_GRID_PLANE, 0.0f, y);
			glVertex3f( DEBUG_HALF_GRID_PLANE, 0.0f, y);
		}

		glVertex3f(DEBUG_HALF_GRID_PLANE, 0.0f,  DEBUG_HALF_GRID_PLANE);
		glVertex3f(DEBUG_HALF_GRID_PLANE, 0.0f, -DEBUG_HALF_GRID_PLANE);

		glVertex3f(DEBUG_HALF_GRID_PLANE,  0.0f, DEBUG_HALF_GRID_PLANE);
		glVertex3f(-DEBUG_HALF_GRID_PLANE, 0.0f,  DEBUG_HALF_GRID_PLANE);
	glEnd();
	
	glPopMatrix();
}
