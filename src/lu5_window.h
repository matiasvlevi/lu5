#ifndef _LU5_WINDOW_H_
#define _LU5_WINDOW_H_

#include <lua.h>
#include <GLFW/glfw3.h>

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

GLFWwindow *lu5_create_glfw_window(lua_State *L, int width, int height, const char *title);

#endif
