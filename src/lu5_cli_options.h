#ifndef __LU5_OPTIONS_H__
#define __LU5_OPTIONS_H__

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
