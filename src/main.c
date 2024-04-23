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

#define SIZE_OF_MAP 1000

#define LU5_NO_WINDOW_ERROR\
    "You need to create a window with the `createWindow` function\n"

#define LU5_FILE_NOT_SPECIFIED\
    "No source path found\n"

#define LU5_FILE_NOT_EXIST(filename)\
    "'%s' is not a valid lua sketch file\n", filename

#define LU5_FILE_EXISTS_ERROR(x)\
    "It seems that %s already exists\n"\
    "We will not overwrite the file\n", x

#define LU5_RUNNING_FILE(filename)\
    "\x1b[46m\x1b[30mRunning >>> \x1b[0m \x1b[36m%s\x1b[0m\n", filename

#define LU5_LUA_ERROR(content)\
    "[\x1b[36mLUA ERROR\x1b[0m]: %s", content

#define LU5_CLOSE\
    "Terminating...\n"

#define LU5_SKETCH_BOILERPLATE \
        "\n"\
        "function setup()\n"\
        "   createWindow(600, 600);\n"\
        "end\n"\
        "\n"\
        "function draw()\n"\
        "   background(51);\n"\
        "end\n"\


int lu5_option_init(int argc, char **argv) 
{

    if (argc != 2) {
        fprintf(stderr, LU5_FILE_NOT_SPECIFIED);
        return 1;
    }

    char *filename = argv[1];
    struct stat buffer;

    if (stat(filename, &buffer) == 0) {

        // Write to 
        fprintf(stderr, LU5_FILE_EXISTS_ERROR(argv[1]));

        // TODO: Ask user if it wishes to continue

        // NON Error return
        return 0;
    }

    FILE *sketch = fopen(argv[1], "w");

    // Write to file
    fprintf(sketch, LU5_SKETCH_BOILERPLATE);

    // Close the file
    fclose(sketch);

    return 0;
}

#define LU5_OPTION_COUNT 2

int lu5_option_help(int, char**);

typedef struct {
    const char *name;
    const char *description;
    const char *example;

    int (*handler)(int, char**);

} lu5_option;

static lu5_option cli_options[LU5_OPTION_COUNT] = {
    {
        .name = "help",
        .description = "Displays this help meny",
        .example = "",
        .handler = lu5_option_help
    },
    {
        .name = "init",
        .description = "Creates a lu5 sketch",
        .example = "lu5 --init mysketch.lua",
        .handler = lu5_option_init
    }
};


int lu5_option_help(int argc, char **argv) 
{   
    for (int i = 0; i < LU5_OPTION_COUNT; i++) {

        printf(
            "\n\x1b[4;36m--%s\x1b[0m  "
            "%s\n",
            cli_options[i].name, 
            cli_options[i].description
        );

        if (cli_options[i].example[0] != '\0') {
            printf(
                "\t\x1b[90mexample: %s\x1b[0m\n",
                cli_options[i].example
            );

        }

    }

    putc('\n', stdout);

    return 0;
}

int handle_option(int argc, char **argv, int i)
{
    char *option_name = argv[i] + 2;

    for (int i = 0; i < LU5_OPTION_COUNT; i++) {
        if (strcmp(option_name, cli_options[i].name) == 0) {
            return cli_options[i].handler(argc, argv);
        }
    }

    return 0;
}

bool handle_args(int argc, char** argv, char **filename) 
{
    bool defaultExec = true;

    // Skip program
    argv++;

    for (int i = 0; i < argc-1; i++) {
        if (
            argv[i][0] == '-' &&
            argv[i][1] == '-'
        ) {

            int err = handle_option(argc-1, argv, i);
            if (err) exit(err);

            defaultExec = false;
            continue;
        } else {
            *filename = argv[i];
        }
    }

    if (*filename) defaultExec = true;

    // If default execution
    if (defaultExec) { 
        // If file name was not found
        if (!(*filename)) {
            fprintf(stderr, LU5_FILE_NOT_SPECIFIED);
            return 1;
        } 
    }

    return defaultExec;
}

int main(int argc, char **argv) {
    char *filename;
    bool defaultExec = handle_args(argc, argv, &filename);

    if (!defaultExec) return 0;
    
    // Read the specified file
    FILE *lua_file = fopen(filename, "r");
    if (!lua_file) {
        fprintf(stderr, LU5_FILE_NOT_EXIST(filename));
        return 1;
    }
    char *lua_source = readFile(lua_file);

    // Close file
    fclose(lua_file);

    // Start lua
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    // Register functions & constants
    registerSymbols(L);
 
    // Run the file
    if (luaL_dostring(L, lua_source) != LUA_OK) {
        fprintf(stderr, LU5_LUA_ERROR(lua_tostring(L, -1)));
    }

    printf(LU5_RUNNING_FILE(filename));
    
    SetTraceLogLevel(LOG_ERROR); 
    // Call the setup function
    LUA_PCALL("setup", 0, 0, 0)
 
    // If window was created in the setup, run main loop
    if (windowExists) {
        update_dynamic_variables(L);
        
        while (!WindowShouldClose()) {
            update_dynamic_variables(L);

            BeginDrawing();
             
            // Call draw
            LUA_PCALL("draw", 0, 0, 0)
            
            EndDrawing();
        }
        
        CloseWindow();
    } else {
        fprintf(stderr, LU5_NO_WINDOW_ERROR);
        return 1;
    }

    puts(LU5_CLOSE);

    // Close lua
    lua_close(L);

    // Free the lua file
    free(lua_source);

    return 0;
}
