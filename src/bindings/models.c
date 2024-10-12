#include "models.h"

#ifndef LU5_WASM
#include <GL/gl.h>
#endif

#include "../lu5_types.h"

#include "../lu5_geometry.h"
#include "../lu5_obj.h"

int loadModel(lua_State *L) 
{
	const char *filepath = lu5_assert_string(L, 1, "loadModel");

	#ifndef LU5_WASM
	lu5_model *model = lu5_load_obj(&lu5, filepath);
	#else
	lu5_model *model = NULL; // TODO: WASM
	// This should be unreachable for now as 
	// we close the window after throwing a warning
	#endif

	if (model) 
	{
		lua_pushlightuserdata(L, model);
	}
	else 
	{
		lua_pushnil(L);
	}

	return 1;
}

int model(lua_State *L)
{
	lu5_model *model = (lu5_model*)lua_touserdata(L, 1);

	if (lu5_has_fill()) 
	{
		#ifndef LU5_WASM
		lu5_apply_color(lu5_style(&lu5)->fill);
		for (int j = 0; j <  model->face_count; j++) 
		{
			// Get face
			lu5_face f = model->faces[j];

			glBegin(f.is_quad ? GL_QUADS : GL_TRIANGLES);

			for (int k = 0; k < (f.is_quad ? 4 : 3); ++k) 
			{
				unsigned int v_index = f.v[k] - 1;
				unsigned int vn_index = f.vn[k] - 1;
				unsigned int vt_index = f.vt[k] - 1;

				if (vn_index < model->normal_count) 
				{
					lu5_glNormal3(model->normals[vn_index].x, 
								  model->normals[vn_index].y, 
								  model->normals[vn_index].z);
				}

				if (vt_index < model->texcoord_count) 
				{
					lu5_glTexCoord2(model->texcoords[vt_index].u, 
									model->texcoords[vt_index].v);
				}

				lu5_glVertex3(model->vertices[v_index].x, 
				  			  model->vertices[v_index].y, 
							  model->vertices[v_index].z);
			}
			glEnd();
		}
		#else
			// TODO: WASM
		#endif
	}

	if (lu5_has_stroke()) 
	{
		#ifndef LU5_WASM
		lu5_apply_color(lu5_style(&lu5)->stroke);
		glLineWidth(lu5_style(&lu5)->strokeWeight);
		glBegin(GL_LINES);

		for (int j = 0; j < model->face_count; j++) 
		{
			lu5_face f = model->faces[j];
			int sides = f.is_quad ? 4 : 3;
			
			for (int k = 0; k < sides; ++k) 
			{
				unsigned int v_index = f.v[k] - 1;
				unsigned int n_index = f.v[(k + 1) % sides] - 1;

				lu5_glVertex3(model->vertices[v_index].x, model->vertices[v_index].y, model->vertices[v_index].z);
				lu5_glVertex3(model->vertices[n_index].x, model->vertices[n_index].y, model->vertices[n_index].z);
			}
		}

		glEnd();
		#else
		// TODO: WASM
		#endif
	}

	return 0;
}
