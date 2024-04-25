#include <stdlib.h>
#include <stdio.h>

#include "lu5_defs.h"
#include "lu5_logger.h"
#include "lu5_cli_options.h"

#include "lu5_state.h"

#include <sys/stat.h>
#include <errno.h>

lu5_option cli_options[LU5_OPTION_COUNT] = {
    {
        .name = "help",
        .description = "Displays this help meny",
        .example = "",
        .handler = lu5_option_help,
        .arg_count = 0
    },
    {
        .name = "init",
        .description = "Creates a lu5 sketch",
        .example = "lu5 --init sketch.lua",
        .handler = lu5_option_init,
        .arg_count = 1
    },
    {
        .name = "log",
        .description = " Set lu5's log level. Value 0 will disable all logs",
        .example = "lu5 sketch.lua --log 1",
        .handler = lu5_option_log,
        .arg_count = 1
    },
};

int lu5_option_log(int argc, char **argv, int idx, int cli_id) {
    if (idx+cli_options[cli_id].arg_count >= argc) {
        LU5_ERROR("%s option expected a log level value from 0 to %i", argv[idx], LU5_WARN_LOG);
        return 1;
    }
    int option_index = idx+cli_options[cli_id].arg_count;

    char *end = NULL;
    int log_level = strtol(argv[option_index], &end, 10);

    /* reset errno to 0 before call */
    errno = 0;

    // Check if error during parsing
    if (
        (argv[option_index] == end) ||
        (errno == ERANGE && log_level == LONG_MIN) ||
        (errno == ERANGE && log_level == LONG_MAX) ||
        (errno == EINVAL) ||
        (errno != 0 && log_level == 0)
    ) {
        LU5_ERROR("Invalid parameter in %s option, expected number but got %s", argv[idx], argv[option_index]);
    }

    // Check if number parsed correctly
    if (
        (errno == 0 && argv[option_index] && !*end) ||
        (errno == 0 && argv[option_index] && *end != 0)
    ) {
        // Set the log level
        lu5.log_level = log_level;
    }
    


    printf ("\n");

    return 0;
}

int lu5_option_init(int argc, char **argv, int idx, int cli_id) 
{
    if (argc != 2) {
        LU5_ERROR(LU5_FILE_NOT_SPECIFIED);
        return 1;
    }

    char *filename = argv[1];
    struct stat buffer;

    // If file exists
    if (stat(filename, &buffer) == 0) {
        
        LU5_ERROR(LU5_FILE_EXISTS_ERROR(argv[1]));

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

int lu5_option_help(int argc, char **argv, int idx, int cli_id) 
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
