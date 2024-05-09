#ifndef _LU5_CLI_OPTIONS_H_
#define _LU5_CLI_OPTIONS_H_

#include <stdbool.h>

#define LU5_OPTION_COUNT 3

typedef struct {
	const char *name;
	const char *description;
	const char *example;
	int arg_count;
	int (*handler)(int, char**, int, int, bool*, char**);
} lu5_option;

extern lu5_option cli_options[LU5_OPTION_COUNT];

int lu5_option_log(int argc, char **argv, int idx, int cli_id, bool* defaultExec, char **filename);
int lu5_option_init(int argc, char **argv, int idx, int cli_id, bool* defaultExec, char **filename);
int lu5_option_help(int argc, char **argv, int idx, int cli_id, bool* defaultExec, char **filename);

#endif
