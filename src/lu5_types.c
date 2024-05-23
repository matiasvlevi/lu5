#include "lu5_types.h"

#include <lualib.h>
#include <lauxlib.h>

LU5_TYPE_BIND(double      , number);
LU5_TYPE_BIND(int         , integer);
LU5_TYPE_BIND(const char *, string);
