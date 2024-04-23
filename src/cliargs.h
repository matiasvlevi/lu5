#ifndef __LU5_CLI_ARGS_H__
#define __LU5_CLI_ARGS_H__

#include <stdbool.h>

int handle_option(int argc, char **argv, int i);

bool handle_args(int argc, char** argv, char **filename);

#endif
