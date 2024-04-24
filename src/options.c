#include <stdlib.h>
#include <stdio.h>

#include "options.h"

#include <sys/stat.h>
#include "defs.h"
#include "options.h"

lu5_option cli_options[LU5_OPTION_COUNT] = {
    {
        .name = "help",
        .description = "Displays this help meny",
        .example = "",
        .handler = lu5_option_help
    },
    {
        .name = "init",
        .description = "Creates a lu5 sketch",
        .example = "lu5 --init sketch.lua",
        .handler = lu5_option_init
    },
    {
        .name = "silent",
        .description = "Hides lu5's logs",
        .example = "lu5 sketch.lua --silent",
        .handler = lu5_option_silent
    },
};

bool silent = false;

int lu5_option_silent(int argc, char **argv) {
   silent = true; 

   return 0;
}

int lu5_option_init(int argc, char **argv) 
{

    if (argc != 2) {
        fprintf(stderr, LU5_FILE_NOT_SPECIFIED);
        return 1;
    }

    char *filename = argv[1];
    struct stat buffer;

    // If file exists
    if (stat(filename, &buffer) == 0) {
        
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
