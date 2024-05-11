#ifndef _LU5_IMAGE_H_
#define _LU5_IMAGE_H_

#include "lu5_state.h"

typedef struct {
	GLuint texture;
	int width;
	int height;
} lu5_image;

lu5_image *lu5_load_image(lu5_State *l5, const char* image_path);

void lu5_render_image(lua_State *L, GLuint texture, double x, double y, double w, double h);

void lu5_close_image(lu5_image *image);

void lu5_close_images(lu5_State *l5);

#endif