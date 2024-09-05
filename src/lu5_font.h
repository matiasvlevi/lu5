#ifndef _LU5_FONT_H_
#define _LU5_FONT_H_

#include <GL/gl.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "./lu5_state.h"

typedef enum {
	LU5_LOADFONT_NONE=0,
	LU5_LOADFONT_MAX,
	LU5_LOADFONT_UNKNOWN_FORMAT,
	LU5_LOADFONT_UNKNOWN,
	LU5_LOADFONT_NO_MEM,
	LU5_LOADFONT_NOT_FOUND
} lu5_loadfont_err;

#define MAX_FONT_SIZE_PX 192

typedef struct lu5_font_s {
	FT_Face face;
	GLuint textures[128];
} lu5_font;

void lu5_init_freetype(lu5_State *l5);

void lu5_load_default_font(lu5_State *l5);
int lu5_load_font(lu5_State *l5, lu5_font **fontId, const char *fontPath);

void lu5_render_text(const char *text, float x, float y, float fontSize, lu5_font *font);

void lu5_close_font(lu5_font *font);

void lu5_close_fonts(lu5_State *l5);


#endif
