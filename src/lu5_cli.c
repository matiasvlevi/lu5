#include "lu5_cli.h"

#include "lu5_defs.h"
#include "lu5_cli_options.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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
    bool defaultExec = false;

    if (argc == 1) {
        // Help menu
        cli_options[0].handler(argc, argv);
        return defaultExec;
    }

    // Skip program
    argv++;

    for (int i = 0; i < argc-1; i++) {
        if (
            argv[i][0] == '-' &&
            argv[i][1] == '-'
        ) {

            int err = handle_option(argc-1, argv, i);
            if (err) exit(err);

            continue;
        } else {
            defaultExec = true;
            *filename = argv[i];
        }
    }

    // If default execution
    if (defaultExec) { 
        // If file name was not found
        if (*filename == NULL) {
            fprintf(stderr, LU5_FILE_NOT_SPECIFIED);
            return 1;
        } 
    }

    return defaultExec;
}

