#ifndef __LU5_OPTIONS_H__
#define __LU5_OPTIONS_H__

#include <stdbool.h>

extern bool silent;


#define LU5_OPTION_COUNT 3

typedef struct {
    const char *name;
    const char *description;
    const char *example;
    int (*handler)(int, char**);
} lu5_option;

extern lu5_option cli_options[LU5_OPTION_COUNT];

int lu5_option_silent(int argc, char **argv);
int lu5_option_init(int argc, char **argv);
int lu5_option_help(int argc, char **argv);


#endif
