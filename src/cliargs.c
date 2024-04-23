#include "cliargs.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "defs.h"
#include "options.h"

//#include <GLFW/glfw3.h>

//GLFWwindow* window;

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

