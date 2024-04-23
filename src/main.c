#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <sys/stat.h>

// LUA
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

// GRAPHICS
#include <GLFW/glfw3.h>
//#include <raylib.h>

// 
#include "readFile.h"
#include "colorArgs.h"
#include "defs.h"
#include "bindings.h"
#include "cliargs.h"
#include "options.h"
#include "window.h"
#include "events.h"

int main(int argc, char **argv) {
    char *filename;
    bool defaultExec = handle_args(argc, argv, &filename);

    if (!defaultExec) return 0;
    
    // Read the specified file
    FILE *lua_file = fopen(filename, "r");
    if (!lua_file) {
        fprintf(stderr, LU5_FILE_NOT_EXIST(filename));
        return 0;
    }

    char *lua_source = readFile(lua_file);

    // Start lua
    lu5.L = luaL_newstate();
    luaL_openlibs(lu5.L);


    lua_pushstring(lu5.L, filename);
    lua_setglobal(lu5.L, "sketch");

    // Register functions & constants
    registerSymbols(lu5.L);

    // Print Running log
    if (!silent) printf(LU5_RUNNING_FILE(filename));
 
    // Run the file
    if (luaL_dostring(lu5.L, lua_source) != LUA_OK) {
        fprintf(stderr, LU5_LUA_ERROR(lua_tostring(lu5.L, -1)));
        goto cleanup;
    }

    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    //glfwSetCursorPosCallback(window, mouse_callback);
    
    lua_getglobal(lu5.L, "setup");
    if (lua_isfunction(lu5.L, -1)) {

        // Call the setup function
        LUA_PCALL(lu5.L, "setup", 0, 0, 0, 1)
    
    } else {
        goto cleanup;
    }

    lua_getglobal(lu5.L, "draw");
    if (!lua_isfunction(lu5.L, -1)) {
        goto cleanup;
    }
 
    // If window was created in the setup, run main loop
    if (!windowExists) {
        
        fprintf(stderr, LU5_NO_WINDOW_ERROR);

        goto cleanup;
    }

    lua_getglobal(lu5.L, "window");
    if (!lua_isuserdata(lu5.L, -1)) {
        goto cleanup;     
    }

    GLFWwindow* window = (GLFWwindow*)lua_touserdata(lu5.L, -1);  
    if (!window) {
        luaL_error(lu5.L, "Invalid GLFWwindow ptr");
        windowExists = false;
        return 0;
    }

    //
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);
    
    update_dynamic_variables(lu5.L, window);
    
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        
        LUA_PCALL(lu5.L, "draw", 0, 0, 0, 1)

        glfwPollEvents();             
        glfwSwapBuffers(window);
        update_dynamic_variables(lu5.L, window);
    }

    puts(LU5_CLOSE);

cleanup:
    glfwTerminate();

     // Close file
    fclose(lua_file);

    // Close lua
    lua_close(lu5.L);

    // Free the lua file
    free(lua_source);

    return 0;
}
