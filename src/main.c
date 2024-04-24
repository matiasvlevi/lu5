#include <stdio.h>
#include <stdlib.h>

#include <lauxlib.h>
#include <lualib.h>

#include "lu5_defs.h"
#include "lu5_state.h"
#include "lu5_cli.h"
#include "lu5_cli_options.h"
#include "lu5_event_callbacks.h"

#include "bindings/bindings.h"

int main(int argc, char **argv) {

    char *filename;
    // return if option ran
    if (!handle_args(argc, argv, &filename)) 
        return 0;

    // Start lua
    lu5.L = luaL_newstate();
    luaL_openlibs(lu5.L);

    lua_pushstring(lu5.L, filename);
    lua_setglobal(lu5.L, "sketch");

    // Register functions & constants
    lu5_register_symbols(lu5.L);
 
    // Print Running log
    if (!silent) 
        printf(LU5_RUNNING_FILE(filename));

    // Run the file
    if (luaL_dofile(lu5.L, filename) != LUA_OK) {
        fprintf(stderr, LU5_LUA_ERROR(lua_tostring(lu5.L, -1)));
        goto cleanup;
    } else {

    }

    // Get the setup function
    lua_getglobal(lu5.L, "setup");
    if (lua_isfunction(lu5.L, -1)) {

        // Call the setup function
        LUA_PCALL_VERBOSE(lu5.L, "setup", 0, 0, 0, 1)
    
    } else {
        // No setup function found, abort
        goto cleanup;
    }

    // If no draw function found, abort
    lua_getglobal(lu5.L, "draw");
    if (!lua_isfunction(lu5.L, -1)) {
        goto cleanup;
    }

    // Check if window was created from lua
    lua_getglobal(lu5.L, "window");
    if (!lua_isuserdata(lu5.L, -1)) {
        fprintf(stderr, LU5_NO_WINDOW_ERROR);
        goto cleanup;     
    }

    // Get the GLFWwindow created from lua 
    GLFWwindow* window = (GLFWwindow*)lua_touserdata(lu5.L, -1);  
    if (!window) {
        fprintf(stderr, "Invalid GLFWwindow pointer\n");
        goto cleanup;
    }

    // Register Event Callbacks
    lu5_register_event_callbacks(window);
   
    lu5_update_dynamic_variables(lu5.L, window);
    
    printf(LU5_RUNNING_FILE("draw"));
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        LUA_PCALL(lu5.L, "draw", 0, 0, 0, 1)

        lu5_poll_events(window);

        lu5_update_dynamic_variables(lu5.L, window);
    }

    if (!silent) puts(LU5_CLOSE);

cleanup:
    glfwTerminate();

    // Close lua
    lua_close(lu5.L);

    return 0;
}
