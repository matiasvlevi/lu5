#ifndef _LU5_FONT_H_
#define _LU5_FONT_H_

#ifndef LU5_WASM

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <ft2build.h>
#include FT_FREETYPE_H

typedef struct lu5_font_s {
	FT_Face face;
	GLuint textures[128];
} lu5_font;
#else
typedef struct lu5_font_s {
	char *name;
} lu5_font;
#endif

#include "./lu5_state.h"
#include "./lu5_decorators.h"
#include "./lu5_color.h"

typedef enum {
	LU5_LOADFONT_NONE=0,
	LU5_LOADFONT_MAX,
	LU5_LOADFONT_UNKNOWN_FORMAT,
	LU5_LOADFONT_UNKNOWN,
	LU5_LOADFONT_NO_MEM,
	LU5_LOADFONT_NOT_FOUND
} lu5_loadfont_err;

#define MAX_FONT_SIZE_PX 192

WASM_IMPORT("env", "lu5_init_freetype") 
void lu5_init_freetype(lu5_State *l5);

WASM_IMPORT("env", "lu5_load_default_font") 
void lu5_load_default_font(lu5_State *l5);

int lu5_load_font(lu5_State *l5, lu5_font **fontId, const char *fontPath);

WASM_IMPORT("env", "lu5_render_text") 
void lu5_render_text(const char *text, float x, float y, float fontSize, int textAlign, lu5_font *font, lu5_color color);

WASM_IMPORT("env", "lu5_load_and_add_font")
lu5_font *lu5_load_and_add_font(lu5_State *l5, const char *font_path);

#ifdef LU5_WASM
WASM_IMPORT("env", "lu5_set_font") void lu5_set_font(const char *);
#endif

void lu5_close_font(lu5_font *font);

WASM_IMPORT("env", "lu5_close_fonts") 
void lu5_close_fonts(lu5_State *l5);


#endif
