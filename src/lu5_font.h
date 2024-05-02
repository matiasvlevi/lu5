#ifndef _LU5_FONT_H_
#define _LU5_FONT_H_
// todo: refactor
#include <GL/gl.h>

#include <ft2build.h>
#include FT_FREETYPE_H

extern FT_Library ft;
extern FT_Face face;

extern GLuint font_textures[128]; // ASCII 0x20-0x7E
                                  
void lu5_font_close();

void lu5_init_freetype();

void lu5_load_font();

void lu5_render_text(const char *text, float x, float y, float fontSize);

#endif
