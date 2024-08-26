#include "lu5_vector.h"

#include <math.h>
#include <string.h>

#include "../lu5_types.h"
#include "../lu5_logger.h"

#include "../lu5_print.h"

lu5_vector* lu5_check_vector(lua_State* L, int index) 
{
	if (lua_isnumber(L, index)) {
		lua_Number scalar = lua_tonumber(L, index);

		lu5_vector *v = (lu5_vector *)lua_newuserdata(L, sizeof(lu5_vector));
		v->x = scalar;
		v->y = scalar;
		v->z = scalar;
		return v;
	}

	return (lu5_vector*)luaL_checkudata(L, index, LU5_VECTOR);
}

static void lu5_new_vector(lua_State *L, lua_Number x, lua_Number y, lua_Number z) 
{
	lu5_vector *v = (lu5_vector *)lua_newuserdata(L, sizeof(lu5_vector));
	luaL_getmetatable(L, LU5_VECTOR);
	lua_setmetatable(L, -2);

	v->x = x;
	v->y = y;
	v->z = z;
}

static int lu5_vector_index(lua_State *L)
{
	lu5_vector *self = lu5_check_vector(L, 1);
	const char *key = luaL_checkstring(L, 2);
	
	// Getting X/Y/Z

	// Get the indexed key length
	lua_len(L, 2);
	lua_Integer key_len = lua_tointeger(L, -1);

	// Get a single vector component and return it
	if (key_len == 1) 
	{
		switch(key[0]) {
			case 'x': lua_pushnumber(L, self->x); break;
			case 'y': lua_pushnumber(L, self->y); break;
			case 'z': lua_pushnumber(L, self->z); break;
		}
		return 1;
	}

	// Try to find mutable method in mt
	luaL_getmetatable(L, LU5_VECTOR);
	lua_getfield(L, -1, key);

	// If found, return it
	if (lua_isfunction(L, -1)) return 1;
	else {
		// try to get the Static method
		lua_getfield(L, -2, "__methods");
		lua_getfield(L, -1, key);
		
		// return it if found
		if (lua_isfunction(L, -1)) return 1;
	}

	// Swizzler-oid indexing
	if (key_len <= 3) 
	{
		// Create a vector from the index key
		lua_Number values[3] = {};
		for (int i = 0; i < key_len; i++) 
		{
			switch(key[i]) {
				case 'x': values[i] = self->x; break;
				case 'y': values[i] = self->y; break;
				case 'z': values[i] = self->z; break;
				default: {
					// 
				}
			}
		}
		lu5_new_vector(L, values[0], values[1], values[2]);
		return 1;
	}

	return 1;
}

static int lu5_vector_newindex(lua_State *L) 
{
	lu5_vector *self = lu5_check_vector(L, 1);
	const char *key = luaL_checkstring(L, 2);
	lua_Number value = lua_tonumber(L, 3);

	// Get the indexed key length
	lua_len(L, 2);
	lua_Integer key_len = lua_tointeger(L, -1);

	// Get a vector component
	if (key_len == 1) 
	{

		switch(key[0]) {
			case 'x': self->x = value; break;
			case 'y': self->y = value; break;
			case 'z': self->z = value; break;
		}
		return 1;
	}

	luaL_error(L, "Could not assign field \x1b[90m'%s'\x1b[0m in \x1b[92mVector\x1b[0m", key);
	return 0;
}

int createVector(lua_State *L) {
	lua_Number x = lu5_assert_number(L, 1, "Vector.new");
	lua_Number y = lu5_assert_number(L, 2, "Vector.new");
	lua_Number z = 0;
	if (lua_isnumber(L, 3)) {
		z = lua_tonumber(L, 3);
	}

	lu5_new_vector(L, x, y, z);

	return 1;
}

int lu5_vector_tostring(lua_State *L)
{
	lu5_vector *self = lu5_check_vector(L, 1);

	int is_3d = (self->z != 0.0f);

	if (is_3d) {
		lua_pushfstring(L, 
			"{ \x1b[33m%f\x1b[0m, \x1b[33m%f\x1b[0m, \x1b[33m%f\x1b[0m }", 
			self->x, self->y, self->z);
	} else {
		lua_pushfstring(L, 
			"{ \x1b[33m%f\x1b[0m, \x1b[33m%f\x1b[0m }", 
			self->x, self->y);
	}

	return 1;
}

int lu5_vector_print(lua_State *L)
{
	lu5_vector_tostring(L);
	const char *str = luaL_checkstring(L, -1);
	printf("%s", str);
	return 0;
}

int lu5_vector_dist(lua_State *L) {
	lu5_vector *p1 = lu5_check_vector(L, 1);
	lu5_vector *p2 = lu5_check_vector(L, 2);

	lua_Number dx = p2->x - p1->x;
	lua_Number dy = p2->y - p1->y;
	lua_Number dz = p2->z - p1->z;

	lua_pushnumber(L, sqrt(dx * dx + dy * dy + dz * dz));

	return 1;
}

int lu5_vector_copy(lua_State *L) {
	lu5_vector *self = lu5_check_vector(L, 1);

	lu5_new_vector(L,
		self->x,
		self->y,
		self->z
	);

	return 1;
}

int lu5_vector_dot(lua_State *L) {
	lu5_vector *a = lu5_check_vector(L, 1);
	lu5_vector *b = lu5_check_vector(L, 2);

	lua_pushnumber(L, 
		a->x * b->x + 
		a->y * b->y + 
		a->z * b->z
	);

	return 1;
}

int lu5_vector_mult(lua_State *L) {
	lu5_vector *a = lu5_check_vector(L, 1);
	lu5_vector *b = lu5_check_vector(L, 2);

	lu5_new_vector(L,
		a->x * b->x,
		a->y * b->y,
		a->z * b->z
	);

	return 1;
}

int lu5_vector_mut_mult(lua_State *L) {
	lu5_vector *self = lu5_check_vector(L, 1);
	lu5_vector *vec = lu5_check_vector(L, 2);

	self->x = self->x * vec->x;
	self->y = self->y * vec->y;
	self->z = self->z * vec->z;

	// Chainable method
	lua_pushvalue(L, 1);
	
	return 1;
}

int lu5_vector_add(lua_State *L) {
	lu5_vector *a = lu5_check_vector(L, 1);
	lu5_vector *b = lu5_check_vector(L, 2);

	lu5_new_vector(L,
		a->x + b->x,
		a->y + b->y,
		a->z + b->z
	);

	return 1;
}

int lu5_vector_mut_add(lua_State *L) {
	lu5_vector *self = lu5_check_vector(L, 1);
	lu5_vector *vec = lu5_check_vector(L, 2);

	self->x = self->x + vec->x;
	self->y = self->y + vec->y;
	self->z = self->z + vec->z;

	// Chainable method
	lua_pushvalue(L, 1);
	
	return 1;
}

int lu5_vector_sub(lua_State *L) {
	lu5_vector *a = lu5_check_vector(L, 1);
	lu5_vector *b = lu5_check_vector(L, 2);

	lu5_new_vector(L,
		a->x - b->x,
		a->y - b->y,
		a->z - b->z
	);

	return 1;
}

int lu5_vector_mut_sub(lua_State *L) {
	lu5_vector *self = lu5_check_vector(L, 1);
	lu5_vector *vec = lu5_check_vector(L, 2);

	self->x = self->x - vec->x; 
	self->y = self->y - vec->y; 
	self->z = self->z - vec->z;

	// Chainable method
	lua_pushvalue(L, 1);
	
	return 1;
}

int lu5_vector_div(lua_State *L) {
	lu5_vector *a = lu5_check_vector(L, 1);
	lu5_vector *b = lu5_check_vector(L, 2);

	lu5_new_vector(L,
		(b->x) ? a->x / b->x : 0,
		(b->y) ? a->y / b->y : 0,
		(b->z) ? a->z / b->z : 0
	);
	
	return 1;
}

int lu5_vector_mut_div(lua_State *L) {
	lu5_vector *self = lu5_check_vector(L, 1);
	lu5_vector *vec = lu5_check_vector(L, 2);

	self->x = (vec->x) ? self->x / vec->x : 0;
	self->y = (vec->y) ? self->y / vec->y : 0;
	self->z = (vec->z) ? self->z / vec->z : 0;

	// Chainable method
	lua_pushvalue(L, 1);
	
	return 1;
}

int lu5_vector_idiv(lua_State *L) {
	lu5_vector *a = lu5_check_vector(L, 1);
	lu5_vector *b = lu5_check_vector(L, 2);

	lu5_new_vector(L,
		(b->x) ? floor(a->x / b->x) : 0,
		(b->y) ? floor(a->y / b->y) : 0,
		(b->z) ? floor(a->z / b->z) : 0
	);

	return 1;
}

int lu5_vector_mut_idiv(lua_State *L) {
	lu5_vector *self = lu5_check_vector(L, 1);
	lu5_vector *vec = lu5_check_vector(L, 2);

	self->x = (vec->x) ? floor(self->x / vec->x) : 0;
	self->y = (vec->y) ? floor(self->y / vec->y) : 0;
	self->z = (vec->z) ? floor(self->z / vec->z) : 0;

	// Chainable method
	lua_pushvalue(L, 1);
	
	return 1;
}


int lu5_vector_eq(lua_State *L) {
	lu5_vector *a = lu5_check_vector(L, 1);
	lu5_vector *b = lu5_check_vector(L, 2);

	lua_pushboolean(L, (
		a->x == b->x &&
		a->y == b->y &&
		a->z == b->z
	));

	return 1;
}

int lu5_vector_mag_sq(lua_State *L) {
	lu5_vector *self = lu5_check_vector(L, 1);

	lua_pushnumber(L, (
		self->x * self->x + self->y * self->y
	));

	return 1;
}

int lu5_vector_mag(lua_State *L) {
	lu5_vector *self = lu5_check_vector(L, 1);

	lua_pushnumber(L, (
		sqrt(self->x * self->x + self->y * self->y)
	));

	return 1;
}

int lu5_vector_normalize(lua_State *L) {
	lu5_vector *self = lu5_check_vector(L, 1);
	lua_Number len = sqrt(self->x * self->x + self->y * self->y);

	lu5_new_vector(L,
		(len) ? (self->x / len) : 0,
		(len) ? (self->y / len) : 0,
		(len) ? (self->z / len) : 0
	);

	return 1;
}

int lu5_vector_mut_normalize(lua_State *L) {
	lu5_vector *self = lu5_check_vector(L, 1);
	lua_Number len = sqrt(self->x * self->x + self->y * self->y);

	self->x = self->x / len;
	self->y = self->y / len;

	return 1;
}


static const luaL_Reg lu5_vector_mut_methods[] = {
	{"add", lu5_vector_mut_add},
	{"sub", lu5_vector_mut_sub},
	{"div", lu5_vector_mut_div},
	{"idiv", lu5_vector_mut_idiv},
	{"mult", lu5_vector_mut_mult},
	{"normalize", lu5_vector_mut_normalize},
	{NULL, NULL}
};

static const luaL_Reg lu5_vector_methods[] = {
	{"new", createVector},
	{"dot", lu5_vector_dot},
	{"dist", lu5_vector_dist},
	{"print", lu5_vector_print},
	{"magSq", lu5_vector_mag_sq},
	{"mag", lu5_vector_mag},
	{"equals", lu5_vector_eq},
	{"copy", lu5_vector_copy},
	{"add", lu5_vector_add},
	{"sub", lu5_vector_sub},
	{"div", lu5_vector_div},
	{"idiv", lu5_vector_idiv},
	{"mult", lu5_vector_mult},
	{"normalize", lu5_vector_normalize},
	{NULL, NULL}
};

int lu5_bind_vector(lua_State *L) {
	luaL_newmetatable(L, LU5_VECTOR);

	// Set the __index and __newindex metamethods
	lua_pushcfunction(L, lu5_vector_index);
	lua_setfield(L, -2, "__index");

	lua_pushcfunction(L, lu5_vector_newindex);
	lua_setfield(L, -2, "__newindex");

	lua_pushcfunction(L, lu5_vector_sub);
	lua_setfield(L, -2, "__sub");

	lua_pushcfunction(L, lu5_vector_add);
	lua_setfield(L, -2, "__add");

	lua_pushcfunction(L, lu5_vector_mult);
	lua_setfield(L, -2, "__mul");

	lua_pushcfunction(L, lu5_vector_div);
	lua_setfield(L, -2, "__div");

	lua_pushcfunction(L, lu5_vector_idiv);
	lua_setfield(L, -2, "__idiv");

	lua_pushcfunction(L, lu5_vector_tostring);
	lua_setfield(L, -2, "__tostring");

	// a .. b = dotprod
	lua_pushcfunction(L, lu5_vector_dot);
	lua_setfield(L, -2, "__concat");

	lua_pushcfunction(L, lu5_vector_eq);
	lua_setfield(L, -2, "__eq");

	lua_pushcfunction(L, lu5_vector_mag);
	lua_setfield(L, -2, "__len");

	// Use a table to store methods and set it as a field on the metatable
	lua_newtable(L);
	
	luaL_setfuncs(L, lu5_vector_methods, 0);
	lua_setfield(L, -2, "__methods");
	
	luaL_setfuncs(L, lu5_vector_mut_methods, 0);

	lua_pushcfunction(L, createVector);
	lua_setglobal(L, "createVector");

	// Push vector methods to the global state
	lua_newtable(L);
	luaL_setfuncs(L, lu5_vector_methods, 0);
	lua_setglobal(L, "Vector");

	return 1;
}
