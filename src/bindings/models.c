#include "models.h"

#include <GL/gl.h>

#include "../lu5_obj.h"
#include "../lu5_types.h"

int loadModel(lua_State *L) 
{
	const char *filepath = lu5_assert_string(L, 1, "loadModel");

	lu5_model *model = lu5_load_obj(&lu5, filepath);

	if (model) lua_pushlightuserdata(L, model);
	else lua_pushnil(L);

	return 1;
}

int model(lua_State *L)
{
	lu5_model *model = (lu5_model*)lua_touserdata(L, 1);

	if (lu5.style.fill.a != 0.0f) {
		LU5_APPLY_COLOR(lu5.style.fill);
		for (int j = 0; j <  model->face_count; j++) {
			lu5_face f = model->faces[j];
			glBegin(f.is_quad ? GL_QUADS : GL_TRIANGLES);

			for (int k = 0; k < (f.is_quad ? 4 : 3); ++k) {
				unsigned int vIndex = f.v[k] - 1;
				unsigned int vnIndex = f.vn[k] - 1;
				unsigned int vtIndex = f.vt[k] - 1;

				if (vnIndex < model->normal_count) {
					glNormal3f(model->normals[vnIndex].x, model->normals[vnIndex].y, model->normals[vnIndex].z);
				}

				if (vtIndex < model->texcoord_count) {
					glTexCoord2f(model->texcoords[vtIndex].u, model->texcoords[vtIndex].v);
				}

				glVertex3f(model->vertices[vIndex].x, model->vertices[vIndex].y, model->vertices[vIndex].z);
			}
			glEnd();
		}
	}

	if (lu5.style.stroke.a != 0.0f) {
		LU5_APPLY_COLOR(lu5.style.stroke);
		glLineWidth(lu5.style.strokeWeight);
		glBegin(GL_LINES);

		for (int j = 0; j < model->face_count; j++) {
			lu5_face f = model->faces[j];
			int sides = f.is_quad ? 4 : 3;
			
			for (int k = 0; k < sides; ++k) {
				unsigned int vIndex1 = f.v[k] - 1;
				unsigned int vIndex2 = f.v[(k + 1) % sides] - 1;

				glVertex3f(model->vertices[vIndex1].x, model->vertices[vIndex1].y, model->vertices[vIndex1].z);
				glVertex3f(model->vertices[vIndex2].x, model->vertices[vIndex2].y, model->vertices[vIndex2].z);
			}
		}

		glEnd();
	}

	return 0;
}
