#ifndef _LU5_MODEL_OBJ_
#define _LU5_MODEL_OBJ_

#include "lu5_state.h"

typedef struct {
    float x, y, z;
} lu5_vertex;

typedef struct {
    float u, v;
} lu5_texcoord;

typedef struct {
    // Vertices indices
    unsigned int v[4];

    // TexCoord indices
    unsigned int vt[4];

    // Normal indices
    unsigned int vn[4];

    int vertex_count;
    int is_quad;
} lu5_face;

typedef struct {
    unsigned int vertex_count;
    lu5_vertex *vertices;

    unsigned int face_count;
    lu5_face *faces;

    unsigned int texcoord_count;
    lu5_texcoord *texcoords;

    unsigned int normal_count;
    lu5_vertex *normals;
} lu5_model;

lu5_model *lu5_load_obj(lu5_State *l5, const char* filename);

void lu5_close_model(lu5_model *model);

void lu5_close_models(lu5_State *l5);

#endif