#include "../lu5_geometry.h"
#include <GL/gl.h>

#include "../../bindings/lu5_math.h"

void lu5_render_ellipsoid_faces(float radius, int detail_x, int detail_y) 
{
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

void lu5_render_ellipsoid_edges(float radius, int detail_x, int detail_y) 
{
	// Draw vertical lines
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

	// Draw horizontal lines
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

