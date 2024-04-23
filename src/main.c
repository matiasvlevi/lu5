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
#include <raylib.h>

// 
#include "readFile.h"
#include "colorArgs.h"
#include "defs.h"
#include "bindings.h"
#include "cliargs.h"
#include "options.h"


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
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // Register functions & constants
    registerSymbols(L);

    // Print Running log
    if (!silent) printf(LU5_RUNNING_FILE(filename));
 
    // Run the file
    if (luaL_dostring(L, lua_source) != LUA_OK) {
        fprintf(stderr, LU5_LUA_ERROR(lua_tostring(L, -1)));
        goto cleanup;
    }

    // Print running

    // Set log level (HIDE LOGS)
    SetTraceLogLevel(LOG_ERROR); 


    
    lua_getglobal(L, "setup");
    if (lua_isfunction(L, -1)) {

        // Call the setup function
        LUA_PCALL("setup", 0, 0, 0)
    
    } else {
        goto cleanup;
    }

    lua_getglobal(L, "draw");
    if (!lua_isfunction(L, -1)) {
        goto cleanup;
    }

 
    // If window was created in the setup, run main loop
    if (!windowExists) {
        
        fprintf(stderr, LU5_NO_WINDOW_ERROR);

        goto cleanup;
    }

    update_dynamic_variables(L);
    
    while (!WindowShouldClose()) {
        update_dynamic_variables(L);

        BeginDrawing();
         
        // Call draw
        LUA_PCALL("draw", 0, 0, 0)
        
        EndDrawing();
    }
    
    CloseWindow();

    puts(LU5_CLOSE);

cleanup:

     // Close file
    fclose(lua_file);

    // Close lua
    lua_close(L);

    // Free the lua file
    free(lua_source);

    return 0;
}
