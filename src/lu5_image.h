#ifndef _LU5_IMAGE_H_
#define _LU5_IMAGE_H_

#include "lu5_state.h"

#ifndef LU5_WASM
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#else
typedef int GLuint;
#endif

typedef struct {
	GLuint texture;
	int width;
	int height;
} lu5_image;

WASM_IMPORT("env", "lu5_load_image") 
lu5_image *lu5_load_image(lu5_State *l5, const char* image_path);

WASM_IMPORT("env", "lu5_image_crop") 
lu5_image *lu5_image_crop(lu5_State *l5, lu5_image *image, int x, int y, int w, int h);

WASM_IMPORT("env", "lu5_render_image") 
void lu5_render_image(lua_State *L, 
	GLuint texture, 
	lua_Number x, lua_Number y, 
	lua_Number w, lua_Number h,
	lu5_color color);

void lu5_close_image(lu5_image *image);

void lu5_close_images(lu5_State *l5);

#endif