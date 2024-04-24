#include "window.h"

#include "../defs.h"
#include "../window.h"

#include <stdio.h>
#include <stdlib.h>
#include <lauxlib.h>

int createWindow(lua_State *L) {
    
    int screenWidth = lua_tointeger(L, 1);
    int screenHeight = lua_tointeger(L, 2);
    LUA_ADD_NUMBER_GLOBAL(L, "width", screenWidth);
    LUA_ADD_NUMBER_GLOBAL(L, "height", screenHeight); 

    lua_getglobal(L, "sketch");
    const char *sketch_path = luaL_checkstring(L, -1);
    if (sketch_path == NULL) return 1;

    int len = luaL_len(L, -1);

    // Add prefix to title
    char* window_title = malloc(len + 10);
    sprintf(window_title, "[lu5]: %s", sketch_path);

    if (!glfwInit()) {
        luaL_error(L, "Failed to initialize GLFW\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(
        screenWidth, screenHeight,     
        window_title, 
        NULL, NULL);

    if (window == NULL)
    {
        luaL_error(L, "Failed to create GLFW window\n");
        glfwTerminate();
        return 0;
    }

    lua_pushlightuserdata(L, window);
    lua_setglobal(L, "window");

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Set callback for when the window is resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Configure for 2D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, screenWidth, screenHeight, 0.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    free(window_title);
    return 0;
}

int background(lua_State *L) {
    GET_COLOR_FROM_LUA_ARGS(L);

    glClearColor(r/255, g/255, b/255, a/255);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    return 0;
}
