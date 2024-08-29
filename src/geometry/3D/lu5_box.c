#include "../lu5_geometry.h"
#include <GL/gl.h>

void lu5_render_box_faces(lua_Number w, lua_Number h, lua_Number d)
{
	glBegin(GL_QUADS);
	// Front face
	lu5_glVertex3(-w, -h,  d);
	lu5_glVertex3( w, -h,  d);
	lu5_glVertex3( w,  h,  d);
	lu5_glVertex3(-w,  h,  d);

	// Back face
	lu5_glVertex3(-w, -h, -d);
	lu5_glVertex3(-w,  h, -d);
	lu5_glVertex3( w,  h, -d);
	lu5_glVertex3( w, -h, -d);

	// Top face
	lu5_glVertex3(-w,  h, -d);
	lu5_glVertex3(-w,  h,  d);
	lu5_glVertex3( w,  h,  d);
	lu5_glVertex3( w,  h, -d);

	// Bottom face
	lu5_glVertex3(-w, -h, -d);
	lu5_glVertex3( w, -h, -d);
	lu5_glVertex3( w, -h,  d);
	lu5_glVertex3(-w, -h,  d);

	// Right face
	lu5_glVertex3( w, -h, -d);
	lu5_glVertex3( w,  h, -d);
	lu5_glVertex3( w,  h,  d);
	lu5_glVertex3( w, -h,  d);

	// Left face
	lu5_glVertex3(-w, -h, -d);
	lu5_glVertex3(-w, -h,  d);
	lu5_glVertex3(-w,  h,  d);
	lu5_glVertex3(-w,  h, -d);
	glEnd();
}

void lu5_render_box_edges(lua_Number w, lua_Number h, lua_Number d)
{
	glBegin(GL_LINES);

	// Front face
	lu5_glVertex3(-w, -h,  d); lu5_glVertex3( w, -h,  d);
	lu5_glVertex3( w, -h,  d); lu5_glVertex3( w,  h,  d);
	lu5_glVertex3( w,  h,  d); lu5_glVertex3(-w,  h,  d);
	lu5_glVertex3(-w,  h,  d); lu5_glVertex3(-w, -h,  d);

	// Back face
	lu5_glVertex3(-w, -h, -d); lu5_glVertex3( w, -h, -d);
	lu5_glVertex3( w, -h, -d); lu5_glVertex3( w,  h, -d);
	lu5_glVertex3( w,  h, -d); lu5_glVertex3(-w,  h, -d);
	lu5_glVertex3(-w,  h, -d); lu5_glVertex3(-w, -h, -d);

	// Connect front and back model->faces
	lu5_glVertex3(-w, -h,  d); lu5_glVertex3(-w, -h, -d);
	lu5_glVertex3( w, -h,  d); lu5_glVertex3( w, -h, -d);
	lu5_glVertex3( w,  h,  d); lu5_glVertex3( w,  h, -d);
	lu5_glVertex3(-w,  h,  d); lu5_glVertex3(-w,  h, -d);

	glEnd();
}
