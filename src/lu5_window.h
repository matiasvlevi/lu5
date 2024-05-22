#ifndef _LU5_WINDOW_H_
#define _LU5_WINDOW_H_

#include <lua.h>
#include <GLFW/glfw3.h>

GLFWwindow *lu5_create_glfw_window(lua_State *L, int width, int height, const char *title);

#endif
