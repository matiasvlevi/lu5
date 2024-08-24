#include "lu5_vector.h"

#include <math.h>
#include <string.h>

#include "../lu5_types.h"
#include "../lu5_logger.h"

#include "../lu5_print.h"

static lu5_vector* lu5_check_vector(lua_State* L, int index) {
    if (lua_isnumber(L, index)) {
        double scalar = lua_tonumber(L, index);

        lu5_vector *v = (lu5_vector *)lua_newuserdata(L, sizeof(lu5_vector));
        v->x = scalar;
        v->y = scalar;
        return v;
    }

    return (lu5_vector*)luaL_checkudata(L, index, LU5_VECTOR);
}

static int lu5_vector_index(lua_State *L) {
    lu5_vector *v = lu5_check_vector(L, 1);
    const char *key = luaL_checkstring(L, 2);


	if (strcmp(key, "x") == 0) {
        lua_pushnumber(L, v->x);
    } else if (strcmp(key, "y") == 0) {
        lua_pushnumber(L, v->y);
    } else {
        // If it's not 'x' or 'y', it might be a method, 
		// let __index go to the methods table.
        luaL_getmetatable(L, LU5_VECTOR);
        lua_getfield(L, -1, "__methods");
        lua_getfield(L, -1, key);
    }
    return 1;
}

static int lu5_vector_newindex(lua_State *L) {
    lu5_vector *v = lu5_check_vector(L, 1);

    const char *key = luaL_checkstring(L, 2);
    float value = (float)luaL_checknumber(L, 3);

    if (strcmp(key, "x") == 0) {
        v->x = value;
    } else if (strcmp(key, "y") == 0) {
        v->y = value;
    } else {
        luaL_error(L, "Invalid property");
    }

    return 0;
}

int createVector(lua_State *L) {
    float x = lu5_assert_number(L, 1, "lu5_vector_.new");
    float y = lu5_assert_number(L, 2, "lu5_vector_.new");

    lu5_vector *v = (lu5_vector *)lua_newuserdata(L, sizeof(lu5_vector));
    luaL_getmetatable(L, LU5_VECTOR);
    lua_setmetatable(L, -2);

    v->x = x;
    v->y = y;

    return 1;
}

int lu5_vector_print(lua_State *L)
{
	lu5_vector *self = lu5_check_vector(L, 1);

	LU5_LOG("{ \x1b[33m%lf\x1b[0m, \x1b[33m%lf\x1b[0m }", 
            self->x, self->y);
	
	return 0;
}

int lu5_vector_dist(lua_State *L) {
    lu5_vector *p1 = lu5_check_vector(L, 1);
    lu5_vector *p2 = lu5_check_vector(L, 2);

    double dy = p2->y - p1->y;
    double dx = p2->x - p1->x; 

    lua_pushnumber(L, sqrt(dx * dx + dy * dy));

    return 1;
}

int lu5_vector_dot(lua_State *L) {
    lu5_vector *a = lu5_check_vector(L, 1);
    lu5_vector *b = lu5_check_vector(L, 2);

    lua_pushnumber(L, a->x * b->x + a->y * b->y);

    return 1;
}

int lu5_vector_mult(lua_State *L) {
    lu5_vector *a = lu5_check_vector(L, 1);
    lu5_vector *b = lu5_check_vector(L, 2);

    lu5_vector *result = (lu5_vector *)lua_newuserdata(L, sizeof(lu5_vector));
    luaL_getmetatable(L, LU5_VECTOR);
    lua_setmetatable(L, -2);

    result->x = a->x * b->x;
    result->y = a->y * b->y;

    return 1;
}

int lu5_vector_add(lua_State *L) {
    lu5_vector *a = lu5_check_vector(L, 1);
    lu5_vector *b = lu5_check_vector(L, 2);

    lu5_vector *result = (lu5_vector *)lua_newuserdata(L, sizeof(lu5_vector));
    luaL_getmetatable(L, LU5_VECTOR);
    lua_setmetatable(L, -2);

    result->x = a->x + b->x;
    result->y = a->y + b->y;

    return 1;
}

static const luaL_Reg lu5_vector_methods[] = {
	{"new", createVector},
	{"add", lu5_vector_add},
	{"mult", lu5_vector_mult},
	{"dot", lu5_vector_dot},
	{"dist", lu5_vector_dist},
	{"print", lu5_vector_print},
	{NULL, NULL}
};

int lu5_bind_vector(lua_State *L) {
    luaL_newmetatable(L, LU5_VECTOR);

    // Set the __index and __newindex metamethods
    lua_pushcfunction(L, lu5_vector_index);
    lua_setfield(L, -2, "__index");
    
    lua_pushcfunction(L, lu5_vector_newindex);
    lua_setfield(L, -2, "__newindex");
    
    // Use a table to store methods and set it as a field on the metatable
    lua_newtable(L);
    
    luaL_setfuncs(L, lu5_vector_methods, 0);
    lua_setfield(L, -2, "__methods");
    
    lua_pushcfunction(L, createVector);
    lua_setglobal(L, "createVector");

	// Push vector methods to the global state
    lua_getfield(L, -1, "__methods");
    lua_setglobal(L, "Vector");

    return 1;
}
