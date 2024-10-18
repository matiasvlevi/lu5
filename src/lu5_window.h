#ifndef _LU5_WINDOW_H_
#define _LU5_WINDOW_H_

#ifdef _WIN32
#include <windows.h>
#endif

#ifndef LU5_WASM
#include <GLFW/glfw3.h>
#endif

#include <lua.h>
#include "lu5_decorators.h"

typedef struct lu5_State_s lu5_State;

/**
 * GL2D
 *
 * 2D Rendering Mode
 */
#define LU5_GL2D 0

/**
 * GL3D
 *
 * 3D Rendering Mode
 */
#define LU5_GL3D 1

// Window definition
#ifdef LU5_WASM
    typedef struct  {} lu5_window; // not needed
#else
    typedef GLFWwindow lu5_window;
#endif

// Draw loop start/stop
#ifdef LU5_WASM
    WASM_IMPORT("env", "lu5_noLoop") void lu5_noLoop();
    WASM_IMPORT("env", "lu5_loop")   void lu5_loop();
#else
    #define lu5_noLoop() lu5.loop = false
    #define lu5_loop()   lu5.loop = true
#endif

/**
 * Create a lu5 window (either glfw for native or html canvas for wasm)
 *
 * @param width Window's width
 * @param height Window's height
 * @param title Window's title
 * @param depth_mode Either `LU5_GL2D` or `LU5_GL3D`.
 */
WASM_IMPORT("env", "lu5_createWindow") 
lu5_window *lu5_create_lu5_window(lua_State *L, int width, int height, const char *title, int depth_mode);

WASM_EXPORT("_lu5_update_window_size")
void lu5_update_window_size(lu5_State *l5, lua_Integer width, lua_Integer height);

#endif
