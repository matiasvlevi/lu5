
#include "shapes3D.h"
#include <GLFW/glfw3.h>
#include <math.h>

#include "../lu5_types.h"
#include "../lu5_state.h"

static void lu5_render_plane(lua_Number size_x, lua_Number size_y) {
	lua_Number half_x = size_x / 2.0f;
	lua_Number half_y = size_y / 2.0f;

	if (lu5.style.fill.a != 0.0f) {
		LU5_APPLY_COLOR(lu5.style.fill);
		glBegin(GL_QUADS);
			glVertex3f(-half_x, -half_y, 0.0f);
			glVertex3f( half_x, -half_y, 0.0f);
			glVertex3f( half_x,  half_y, 0.0f);
			glVertex3f(-half_x,  half_y, 0.0f);
		glEnd();
	}

	if (lu5.style.stroke.a != 0.0f) {
		LU5_APPLY_COLOR(lu5.style.stroke);
		glLineWidth(lu5.style.strokeWeight);
		glBegin(GL_LINE_LOOP);
			glVertex3f(-half_x, -half_y, 0.0f);
			glVertex3f( half_x, -half_y, 0.0f);
			glVertex3f( half_x,  half_y, 0.0f);
			glVertex3f(-half_x,  half_y, 0.0f);
			glVertex3f( half_x, -half_y, 0.0f);
			glVertex3f(-half_x,  half_y, 0.0f);
		glEnd();
	}
}

void lu5_render_ellipsoid(float radius, int detail_x, int detail_y) {

	if (lu5.style.fill.a != 0.0f) {
		LU5_APPLY_COLOR(lu5.style.fill);
		for (int i = 0; i < detail_y; i++) {
			float v0 = (float)i / detail_y;
			float phi0 = M_PI * v0 - M_PI / 2;
			float cosPhi0 = cosf(phi0);
			float sinPhi0 = sinf(phi0);

			float v1 = (float)(i + 1) / detail_y;
			float phi1 = M_PI * v1 - M_PI / 2;
			float cosPhi1 = cosf(phi1);
			float sinPhi1 = sinf(phi1);

			glBegin(GL_QUAD_STRIP);
			for (int j = 0; j <= detail_x; j++) {
				float u = (float)j / detail_x;
				float theta = 2 * M_PI * u;
				float cosTheta = cosf(theta);
				float sinTheta = sinf(theta);

				float x0 = cosPhi0 * sinTheta;
				float y0 = sinPhi0;
				float z0 = cosPhi0 * cosTheta;

				float x1 = cosPhi1 * sinTheta;
				float y1 = sinPhi1;
				float z1 = cosPhi1 * cosTheta;

				glVertex3f(radius * x0, radius * y0, radius * z0);
				glVertex3f(radius * x1, radius * y1, radius * z1);
			}
			glEnd();
		}
	}

	if (lu5.style.stroke.a != 0.0f) {
		// Draw sphere edges
		LU5_APPLY_COLOR(lu5.style.stroke);
		glLineWidth(lu5.style.strokeWeight * 0.65);

		// Draw strokes 1 unit further
		radius += 0.2f;

		// Draw longitudinal (vertical) lines
		for (int i = 0; i <= detail_y; i++) {
			float v = (float)i / detail_y;
			float phi = M_PI * v - M_PI / 2;
			float cosPhi = cosf(phi);
			float sinPhi = sinf(phi);

			glBegin(GL_LINE_LOOP);
			for (int j = 0; j <= detail_x; j++) {
				float u = (float)j / detail_x;
				float theta = 2 * M_PI * u;
				float cosTheta = cosf(theta);
				float sinTheta = sinf(theta);

				float x = cosPhi * sinTheta;
				float y = sinPhi;
				float z = cosPhi * cosTheta;

				glVertex3f(radius * x, radius * y, radius * z);
			}
			glEnd();
		}

		// Draw latitudinal (horizontal) lines
		for (int j = 0; j <= detail_x; j++) {
			glBegin(GL_LINE_LOOP);
			for (int i = 0; i <= detail_y; i++) {
				float v = (float)i / detail_y;
				float phi = M_PI * v - M_PI / 2;
				float cosPhi = cosf(phi);
				float sinPhi = sinf(phi);

				float u = (float)j / detail_x;
				float theta = 2 * M_PI * u;
				float cosTheta = cosf(theta);
				float sinTheta = sinf(theta);

				float x = cosPhi * sinTheta;
				float y = sinPhi;
				float z = cosPhi * cosTheta;

				glVertex3f(radius * x, radius * y, radius * z);
			}
			glEnd();
		}

		// Draw diagonal lines
		for (int i = 0; i < detail_y; i++) {
			float v1 = (float)i / detail_y;
			float phi1 = M_PI * v1 - M_PI / 2;
			float cosPhi1 = cosf(phi1);
			float sinPhi1 = sinf(phi1);

			float v2 = (float)(i + 1) / detail_y;
			float phi2 = M_PI * v2 - M_PI / 2;
			float cosPhi2 = cosf(phi2);
			float sinPhi2 = sinf(phi2);

			glBegin(GL_LINES);
			for (int j = 0; j < detail_x; j++) {
				float u1 = (float)j / detail_x;
				float theta1 = 2 * M_PI * u1;
				float cosTheta1 = cosf(theta1);
				float sinTheta1 = sinf(theta1);

				float u2 = (float)(j + 1) / detail_x;
				float theta2 = 2 * M_PI * u2;
				float cosTheta2 = cosf(theta2);
				float sinTheta2 = sinf(theta2);

				// First diagonal from (i, j) to (i + 1, j + 1)
				float x1 = cosPhi1 * sinTheta1;
				float y1 = sinPhi1;
				float z1 = cosPhi1 * cosTheta1;
				float x2 = cosPhi2 * sinTheta2;
				float y2 = sinPhi2;
				float z2 = cosPhi2 * cosTheta2;
				glVertex3f(radius * x1, radius * y1, radius * z1);
				glVertex3f(radius * x2, radius * y2, radius * z2);
			}
			glEnd();
		}
	}
}

void lu5_render_cube(float width, float height, float depth) 
{
	float w = width / 2.0f;
	float h = height / 2.0f;
	float d = depth / 2.0f;

	if (lu5.style.fill.a != 0.0f) {
		LU5_APPLY_COLOR(lu5.style.fill);
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

	if (lu5.style.stroke.a != 0.0f) {
		LU5_APPLY_COLOR(lu5.style.stroke);
		glLineWidth(lu5.style.strokeWeight);


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
}

int plane(lua_State *L) 
{
	lua_Number size_x = lu5_assert_number(L, 1, "plane");
	lua_Number size_y = size_x;
	
	if (lua_isnumber(L, 2)) {
		size_y = lua_tonumber(L, 2);
	}

	lu5_render_plane(size_x, size_y);

	return 0;
}

int box(lua_State *L) 
{
	lua_Number w = lu5_assert_number(L, 1, "box");

	lua_Number h = w;
	if (lua_isnumber(L, 2)) {
		h = lua_tonumber(L, 2);
	}
	
	lua_Number d = h;
	if (lua_isnumber(L, 3)) {
		d = lua_tonumber(L, 3);
	}

	lu5_render_cube(w, h, d);

	return 0;
}

int sphere(lua_State *L) 
{
	lua_Number radius = lu5_assert_number(L, 1, "sphere");

	lua_Number detail_x = 24;
	if (lua_isnumber(L, 2)) {
		detail_x = lua_tonumber(L, 2);
	}
	
	lua_Number detail_y = 16;
	if (lua_isnumber(L, 3)) {
		detail_y = lua_tonumber(L, 3);
	}

	lu5_render_ellipsoid(radius, detail_x, detail_y);

	return 0;
}

int debugMode(lua_State *L) 
{
	float half_x = 200.0f;
	float half_y = 200.0f;
	float step = 20.0f;
	
	glPushMatrix();
		glTranslatef(-half_x - 1, -half_x, -half_y - 1);
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
		glLineWidth(6);
		glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(100.0f, 0.0f, 0.0f);
		glEnd();

		glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		glLineWidth(6);
		glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 100.0f, 0.0f);
		glEnd();

		glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		glLineWidth(6);
		glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 100.0f);
		glEnd();
	glPopMatrix();

	glPushMatrix();
	// Plane grid
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glLineWidth(2);
	glBegin(GL_LINES);
		for (float x = -half_x; x < half_x; x += step) {
			glVertex3f(x, 0.0f, -half_y);
			glVertex3f(x, 0.0f, half_y);
		}

		for (float y = -half_y; y < half_y; y += step) {
			glVertex3f(-half_x, 0.0f, y);
			glVertex3f( half_x, 0.0f, y);
		}

		glVertex3f(half_x, 0.0f,  half_y);
		glVertex3f(half_x, 0.0f, -half_y);

		glVertex3f(half_x,  0.0f, half_y);
		glVertex3f(-half_x, 0.0f,  half_y);
	glEnd();
	
	glPopMatrix();

	LU5_APPLY_COLOR(lu5.style.stroke);
	glLineWidth(lu5.style.strokeWeight);
	return 0;
}

