#ifndef __LU5_CLI_ARGS_H__
#define __LU5_CLI_ARGS_H__

#include <stdbool.h>

int handle_option(int argc, char **argv, int idx, int* offset, bool* defaultExec, char **filename);

bool handle_args(int argc, char** argv, char **filename);

#endif
