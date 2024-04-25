#include "lu5_cli.h"

#include "lu5_logger.h"
#include "lu5_cli_options.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int handle_option(int argc, char **argv, int idx, int* offset)
{
    char *option_name = argv[idx] + 2; // skip 2 dashes

    for (int i = 0; i < LU5_OPTION_COUNT; i++) {
        // Compare name in list
        if (strcmp(option_name, cli_options[i].name) == 0) {
            *offset = cli_options[i].arg_count;
            return cli_options[i].handler(argc, argv, idx, i);
        }
    }

    return 0;
}

bool handle_args(int argc, char** argv, char **filename) 
{
    bool defaultExec = false;

    if (argc == 1) {
        // Help menu
        cli_options[0].handler(argc, argv, 1, 0);
        return defaultExec;
    }

    // Skip program
    argv++;

    for (int i = 0; i < argc-1; i++) {
        if (
            argv[i][0] == '-' &&
            argv[i][1] == '-' 
        ) {
            int offset;
            int err = handle_option(argc-1, argv, i, &offset);
            if (err) exit(err);

            // skip arguments
            i += offset;
        } else if(!defaultExec) {
            *filename = argv[i];

            defaultExec = true;
        }
    }

    // If default execution
    if (defaultExec) { 
        // If file name was not found
        if (*filename == NULL) {
            LU5_ERROR(LU5_FILE_NOT_SPECIFIED);
            return 1;
        } 
    }

    return defaultExec;
}

