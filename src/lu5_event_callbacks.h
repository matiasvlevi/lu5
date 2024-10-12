#ifndef _LU5_EVENTS_CALLBACKS_H_
#define _LU5_EVENTS_CALLBACKS_H_

#include "lu5_state.h"

void lu5_register_event_callbacks(lu5_State *l5);

WASM_EXPORT("_lu5_mouse_cursor_callback") 
void lu5_mouse_cursor_callback(lu5_window* window, double xpos, double ypos);

WASM_EXPORT("_lu5_mouse_button_callback") 
void lu5_mouse_button_callback(lu5_window* window, int button, int action, int mods);

WASM_EXPORT("_lu5_mouse_scroll_callback")
void lu5_mouse_scroll_callback(lu5_window* window, double xoffset, double yoffset);

WASM_EXPORT("_lu5_key_callback")
void lu5_key_callback(lu5_window* window, int key, int scancode, int action, int mods);

#ifdef LU5_WASM
// Import re-implemented glfw functions in JS
WASM_IMPORT("env", "lu5_getCursorPos") 
void glfwGetCursorPos(void*, double*, double*);

WASM_IMPORT("env", "lu5_windowShouldClose") 
int glfwWindowShouldClose(void*);

WASM_IMPORT("env", "lu5_pollEvents")
void glfwPollEvents();

WASM_IMPORT("env", "lu5_swapBuffers")
void glfwSwapBuffers(lu5_window *window);

WASM_IMPORT("env", "lu5_GetKeyName")
const char *glfwGetKeyName(char key, int code);

#define GLFW_RELEASE 0
#define GLFW_PRESS 1
#define GLFW_REPEAT 2
#define GLFW_MOD_CONTROL 2
#define GLFW_MOD_SHIFT 1
#define GLFW_MOD_CAPS_LOCK 4

#endif

#endif
