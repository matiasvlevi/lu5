#include "lu5_obj.h"

#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <string.h>

#include "lu5_fs.h"
#include "lu5_list.h"

#define MODEL_DEFAULT_SCALE 1.0f

lu5_model *lu5_load_obj(lu5_State *l5, const char* filename) 
{
	FILE* file = lu5_open_file(filename, "r");
	if (!file) {
		return NULL;
	}

	lu5_model *model = (lu5_model*)malloc(sizeof(lu5_model));
	model->vertex_count = 0;
	model->texcoord_count = 0;
	model->normal_count = 0;
	model->face_count = 0;

	char line[256];
	while (fgets(line, sizeof(line), file)) {
		if (strncmp(line, "v ", 2) == 0) {
			model->vertex_count++;
		} else if (strncmp(line, "vt ", 3) == 0) {
			model->texcoord_count++;
		} else if (strncmp(line, "vn ", 3) == 0) {
			model->normal_count++;
		} else if (strncmp(line, "f ", 2) == 0) {
			model->face_count++;
		}
	}

	rewind(file);
	
	// Allocate arrays
	model->vertices = (lu5_vertex*)malloc(model->vertex_count * sizeof(lu5_vertex));
	model->faces = (lu5_face*)malloc(model->face_count * sizeof(lu5_face));
	model->normals = (lu5_vertex*)malloc(model->normal_count * sizeof(lu5_vertex));
	model->texcoords = (lu5_texcoord*)malloc(model->texcoord_count * sizeof(lu5_texcoord));

	int vertex_index = 0;
	int face_index = 0;
	int normal_index = 0;
	int texcoord_index = 0;
	
	while (fgets(line, sizeof(line), file)) {
		if (strncmp(line, "v ", 2) == 0) {
			sscanf(line, "v %f %f %f", 
				&model->vertices[vertex_index].x, 
				&model->vertices[vertex_index].y, 
				&model->vertices[vertex_index].z
			);

			// Scale
			model->vertices[vertex_index].x *= MODEL_DEFAULT_SCALE; 
			model->vertices[vertex_index].y *= MODEL_DEFAULT_SCALE; 
			model->vertices[vertex_index].z *= MODEL_DEFAULT_SCALE;
			
			vertex_index++;
		} else if (strncmp(line, "vt ", 3) == 0) {
			sscanf(line, "vt %f %f", 
				&model->texcoords[texcoord_index].u, 
				&model->texcoords[texcoord_index].v
			);
			texcoord_index++;
		} else if (strncmp(line, "vn ", 3) == 0) {
			sscanf(line, "vn %f %f %f", 
				&model->normals[normal_index].x, 
				&model->normals[normal_index].y, 
				&model->normals[normal_index].z
			);
			normal_index++;
		} else if (strncmp(line, "f ", 2) == 0) {
			lu5_face* face = &model->faces[face_index];
			char* ptr = strchr(line, '/');
			if (ptr) {
				face->vertex_count = sscanf(line, "f %u/%u/%u %u/%u/%u %u/%u/%u %u/%u/%u",
										&face->v[0], &face->vt[0], &face->vn[0],
										&face->v[1], &face->vt[1], &face->vn[1],
										&face->v[2], &face->vt[2], &face->vn[2],
										&face->v[3], &face->vt[3], &face->vn[3]);
			}  else if (strstr(line, "//")) {
				sscanf(line, "f %u//%u %u//%u %u//%u %u//%u",
                       &face->v[0], &face->vn[0], &face->v[1], &face->vn[1],
                       &face->v[2], &face->vn[2], &face->v[3], &face->vn[3]);
                face->vertex_count = (face->v[3] != 0) ? 4 : 3;

				// Clear unused texture and normal indices
				face->vt[0] = 0;
				face->vt[1] = 0;
				face->vt[2] = 0;
				face->vt[3] = 0;
			} else {
				// Face does not have slashes, handle format: f v1 v2 v3 ...
				face->vertex_count = sscanf(line, "f %u %u %u %u",
										&face->v[0], &face->v[1], &face->v[2], &face->v[3]);
				// Clear unused texture and normal indices
				face->vt[0] = face->vn[0] = 0;
				face->vt[1] = face->vn[1] = 0;
				face->vt[2] = face->vn[2] = 0;
				face->vt[3] = face->vn[3] = 0;
			}
			face->is_quad = (face->vertex_count == 4 || face->vertex_count == 12) ? 1 : 0;

			face_index++;
		}
	}
	
	fclose(file);

	// Free later with lu5_close_image
	// Add the texture's GLuint ptr to the list
	lu5_list_push(&(l5->models), model, sizeof(lu5_model));

	return model;
}

void lu5_close_model(lu5_model *model) 
{
	if (model != NULL) {
		free(model->vertices);
		free(model->faces);
		free(model);
	}
}

void lu5_close_models(lu5_State *l5) 
{
	lu5_list_iter_close(l5->models, (void (*)(void*))lu5_close_model);
	l5->models = NULL;
}
