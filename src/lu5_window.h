#ifndef _LU5_WINDOW_H_
#define _LU5_WINDOW_H_

#include <lua.h>
#include <GLFW/glfw3.h>

#define LU5_GL2D 0
#define LU5_GL3D 1

GLFWwindow *lu5_create_glfw_window(lua_State *L, int width, int height, const char *title, int depth_mode);

#endif
