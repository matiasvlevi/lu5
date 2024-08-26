#ifndef _LU5_STYLE_H_
#define _LU5_STYLE_H_

#include "lu5_color.h"

typedef struct lu5_font_s lu5_font;

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

#define LU5_SET_DEFAULT_STYLE(s)\
	(s)->strokeWeight = 2;\
	(s)->stroke = LU5_BLACK;\
	(s)->fill = LU5_WHITE;\
	(s)->fontSize = 22;\
	(s)->font_current = NULL;\

typedef struct {
	lu5_color fill;
	lu5_color stroke;
	lua_Number strokeWeight;
	lua_Number fontSize;

	// current font reference
	lu5_font *font_current;
} lu5_style_setting_t;

#endif
