#ifndef __LU5_RANDOM_H__
#define __LU5_RANDOM_H__

#include <lua.h>
#include "./lu5_decorators.h"

WASM_IMPORT("env", "lu5_time_seed") lua_Integer lu5_time_seed(void);

#endif