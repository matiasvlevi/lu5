#ifndef _LU5_CORE_H_
#define _LU5_CORE_H_

#include "./lu5_state.h"

void lu5_init(lu5_State *l5);

void lu5_close(lu5_State *l5);

int lu5_run_sketch(lu5_State *l5, const char *filename);

#endif