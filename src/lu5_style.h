#ifndef _LU5_STYLE_H_
#define _LU5_STYLE_H_

#include "lu5_color.h"
#include "bindings/setting.h"
#include "bindings/typography.h"

typedef struct lu5_State_s lu5_State;
typedef struct lu5_font_s lu5_font;

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

#define lu5_style(l5)\
    ((l5)->style_stack[(l5)->style_stack_len - 1])

#define lu5_has_stroke()\
	(lu5_style(&lu5)->strokeWeight != 0.0f && (lu5_style(&lu5)->stroke.a) != 0.0f)

#define lu5_has_fill()\
	((lu5_style(&lu5)->fill.a) != 0.0f)

#define lu5_set_style(s)\
	(s)->rectMode = LU5_RECTMODE_CORNER;\
	(s)->textAlign = LU5_TEXTALIGN_LEFT;\
	(s)->fill = LU5_WHITE;\
	(s)->stroke = LU5_BLACK;\
	(s)->strokeWeight = 2;\
	(s)->fontSize = 22;\
	(s)->font_current = NULL;\

typedef struct lu5_style_setting_t {
	uint8_t rectMode;
	uint8_t textAlign;

	lu5_color fill;
	lu5_color stroke;
	lua_Number strokeWeight;
	lua_Number fontSize;

	// current font reference
	lu5_font *font_current;
} lu5_style_setting;

void lu5_style_push(lu5_State *l5, lu5_style_setting *style);
void lu5_style_pop(lu5_State *l5);
void lu5_style_clear(lu5_State *l5);

#endif
