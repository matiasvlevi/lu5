#include "../lu5_geometry.h"
#include <GL/gl.h>

void lu5_render_box_faces(float w, float h, float d)
{
	glBegin(GL_QUADS);
	// Front face
	glVertex3f(-w, -h,  d);
	glVertex3f( w, -h,  d);
	glVertex3f( w,  h,  d);
	glVertex3f(-w,  h,  d);

	// Back face
	glVertex3f(-w, -h, -d);
	glVertex3f(-w,  h, -d);
	glVertex3f( w,  h, -d);
	glVertex3f( w, -h, -d);

	// Top face
	glVertex3f(-w,  h, -d);
	glVertex3f(-w,  h,  d);
	glVertex3f( w,  h,  d);
	glVertex3f( w,  h, -d);

	// Bottom face
	glVertex3f(-w, -h, -d);
	glVertex3f( w, -h, -d);
	glVertex3f( w, -h,  d);
	glVertex3f(-w, -h,  d);

	// Right face
	glVertex3f( w, -h, -d);
	glVertex3f( w,  h, -d);
	glVertex3f( w,  h,  d);
	glVertex3f( w, -h,  d);

	// Left face
	glVertex3f(-w, -h, -d);
	glVertex3f(-w, -h,  d);
	glVertex3f(-w,  h,  d);
	glVertex3f(-w,  h, -d);
	glEnd();
}

void lu5_render_box_edges(float w, float h, float d)
{
	glBegin(GL_LINES);

	// Front face
	glVertex3f(-w, -h,  d); glVertex3f( w, -h,  d);
	glVertex3f( w, -h,  d); glVertex3f( w,  h,  d);
	glVertex3f( w,  h,  d); glVertex3f(-w,  h,  d);
	glVertex3f(-w,  h,  d); glVertex3f(-w, -h,  d);

	// Back face
	glVertex3f(-w, -h, -d); glVertex3f( w, -h, -d);
	glVertex3f( w, -h, -d); glVertex3f( w,  h, -d);
	glVertex3f( w,  h, -d); glVertex3f(-w,  h, -d);
	glVertex3f(-w,  h, -d); glVertex3f(-w, -h, -d);

	// Connect front and back model->faces
	glVertex3f(-w, -h,  d); glVertex3f(-w, -h, -d);
	glVertex3f( w, -h,  d); glVertex3f( w, -h, -d);
	glVertex3f( w,  h,  d); glVertex3f( w,  h, -d);
	glVertex3f(-w,  h,  d); glVertex3f(-w,  h, -d);

	glEnd();
}
