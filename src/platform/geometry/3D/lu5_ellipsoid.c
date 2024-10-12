#include "../../../lu5_geometry.h"
#include <GL/gl.h>

#include "../../../bindings/lu5_math.h"

void lu5_render_ellipsoid_faces(
	lua_Number radius, 
	lua_Integer detail_x, 
	lua_Integer detail_y,
	lu5_color color) 
{
	lu5_apply_color(color);
	for (lua_Integer i = 0; i < detail_y; i++) {
		lua_Number v0 = (lua_Number)i / detail_y;
		lua_Number phi0 = M_PI * v0 - M_PI / 2;
		lua_Number cosPhi0 = cosf(phi0);
		lua_Number sinPhi0 = sinf(phi0);

		lua_Number v1 = (lua_Number)(i + 1) / detail_y;
		lua_Number phi1 = M_PI * v1 - M_PI / 2;
		lua_Number cosPhi1 = cosf(phi1);
		lua_Number sinPhi1 = sinf(phi1);

		glBegin(GL_QUAD_STRIP);
		for (lua_Integer j = 0; j <= detail_x; j++) {
			lua_Number u = (lua_Number)j / detail_x;
			lua_Number theta = 2 * M_PI * u;
			lua_Number cosTheta = cosf(theta);
			lua_Number sinTheta = sinf(theta);

			lua_Number x0 = cosPhi0 * sinTheta;
			lua_Number y0 = sinPhi0;
			lua_Number z0 = cosPhi0 * cosTheta;

			lua_Number x1 = cosPhi1 * sinTheta;
			lua_Number y1 = sinPhi1;
			lua_Number z1 = cosPhi1 * cosTheta;

			lu5_glVertex3(radius * x0, radius * y0, radius * z0);
			lu5_glVertex3(radius * x1, radius * y1, radius * z1);
		}
		glEnd();
	}
}

void lu5_render_ellipsoid_edges(
	lua_Number radius, 
	lua_Integer detail_x, 
	lua_Integer detail_y,
	lu5_color color) 
{
	lu5_apply_color(color);
	// Draw vertical lines
	for (lua_Integer i = 0; i <= detail_y; i++) {
		lua_Number v = (lua_Number)i / detail_y;
		lua_Number phi = M_PI * v - M_PI / 2;
		lua_Number cosPhi = cosf(phi);
		lua_Number sinPhi = sinf(phi);

		glBegin(GL_LINE_LOOP);
		for (lua_Integer j = 0; j <= detail_x; j++) {
			lua_Number u = (lua_Number)j / detail_x;
			lua_Number theta = 2 * M_PI * u;
			lua_Number cosTheta = cosf(theta);
			lua_Number sinTheta = sinf(theta);

			lua_Number x = cosPhi * sinTheta;
			lua_Number y = sinPhi;
			lua_Number z = cosPhi * cosTheta;

			lu5_glVertex3(radius * x, radius * y, radius * z);
		}
		glEnd();
	}

	// Draw horizontal lines
	for (lua_Integer j = 0; j <= detail_x; j++) {
		glBegin(GL_LINE_LOOP);
		for (lua_Integer i = 0; i <= detail_y; i++) {
			lua_Number v = (lua_Number)i / detail_y;
			lua_Number phi = M_PI * v - M_PI / 2;
			lua_Number cosPhi = cosf(phi);
			lua_Number sinPhi = sinf(phi);

			lua_Number u = (lua_Number)j / detail_x;
			lua_Number theta = 2 * M_PI * u;
			lua_Number cosTheta = cosf(theta);
			lua_Number sinTheta = sinf(theta);

			lua_Number x = cosPhi * sinTheta;
			lua_Number y = sinPhi;
			lua_Number z = cosPhi * cosTheta;

			lu5_glVertex3(radius * x, radius * y, radius * z);
		}
		glEnd();
	}

	// Draw diagonal lines
	for (lua_Integer i = 0; i < detail_y; i++) {
		lua_Number v1 = (lua_Number)i / detail_y;
		lua_Number phi1 = M_PI * v1 - M_PI / 2;
		lua_Number cosPhi1 = cosf(phi1);
		lua_Number sinPhi1 = sinf(phi1);

		lua_Number v2 = (lua_Number)(i + 1) / detail_y;
		lua_Number phi2 = M_PI * v2 - M_PI / 2;
		lua_Number cosPhi2 = cosf(phi2);
		lua_Number sinPhi2 = sinf(phi2);

		glBegin(GL_LINES);
		for (lua_Integer j = 0; j < detail_x; j++) {
			lua_Number u1 = (lua_Number)j / detail_x;
			lua_Number theta1 = 2 * M_PI * u1;
			lua_Number cosTheta1 = cosf(theta1);
			lua_Number sinTheta1 = sinf(theta1);

			lua_Number u2 = (lua_Number)(j + 1) / detail_x;
			lua_Number theta2 = 2 * M_PI * u2;
			lua_Number cosTheta2 = cosf(theta2);
			lua_Number sinTheta2 = sinf(theta2);

			// First diagonal from (i, j) to (i + 1, j + 1)
			lua_Number x1 = cosPhi1 * sinTheta1;
			lua_Number y1 = sinPhi1;
			lua_Number z1 = cosPhi1 * cosTheta1;
			lua_Number x2 = cosPhi2 * sinTheta2;
			lua_Number y2 = sinPhi2;
			lua_Number z2 = cosPhi2 * cosTheta2;
			lu5_glVertex3(radius * x1, radius * y1, radius * z1);
			lu5_glVertex3(radius * x2, radius * y2, radius * z2);
		}
		glEnd();
	}
}

