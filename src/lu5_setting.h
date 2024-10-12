#ifndef _LU5_SETTING_H_
#define _LU5_SETTING_H_

#include "lu5_decorators.h"
#include "lu5_color.h"

#ifdef LU5_WASM
WASM_IMPORT("env", "lu5_glVertex2")  void lu5_glVertex2(lua_Number x, lua_Number y);
#endif

WASM_IMPORT("env", "lu5_glBegin")    void lu5_glBegin(int shape_type, lu5_color color);
WASM_IMPORT("env", "lu5_glEnd")      void lu5_glEnd();
WASM_IMPORT("env", "lu5_background") void lu5_background(lu5_color color);
WASM_IMPORT("env", "lu5_PushMatrix") void glPushMatrix(void);
WASM_IMPORT("env", "lu5_PopMatrix") void glPopMatrix(void);

#endif