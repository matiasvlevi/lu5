#ifndef _LU5_VECTOR_BINDINGS_H_
#define _LU5_VECTOR_BINDINGS_H_

#include <lua.h>
#include <lauxlib.h>

#define LU5_VECTOR_METHOD_COUNT 4
#define LU5_VECTOR "lu5_vector_"

typedef struct {
	double x;
	double y;
} lu5_vector;

int lu5_bind_vector(lua_State *L);

#endif
