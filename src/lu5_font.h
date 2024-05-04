#ifndef _LU5_FONT_H_
#define _LU5_FONT_H_

#include <GL/gl.h>

#include "./lu5_state.h"

typedef enum {
    LOADFONT_NONE=0,
    LOADFONT_MAX,
    LOADFONT_UNKNOWN_FORMAT,
    LOADFONT_UNKNOWN
} lu5_loadfont_err;



void lu5_close_font(lu5_font *font);
void lu5_close_fonts(lu5_State *l5);

void lu5_init_freetype(lu5_State *l5);

int lu5_load_font(lu5_State *l5, const char *fontPath, int *fontId);

void lu5_render_text(const char *text, float x, float y, float fontSize, lu5_font *font);

#endif
