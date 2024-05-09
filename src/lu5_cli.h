#ifndef _LU5_CLI_H_
#define _LU5_CLI_H_

#include <stdbool.h>

int handle_option(int argc, char **argv, int idx, int* offset, bool* defaultExec, char **filename);

bool handle_args(int argc, char** argv, char **filename);

#endif
