#include "classes.h"
#include "../lu5_logger.h"

#include <lauxlib.h>

/**
 * Get the number of arguments based on a function declaration 
 * 
 * @param L The lua state
 *
 * @return int The number of arguments
 */
static int lu5_get_declaration_argc(lua_State *L, int index) {
	// Get arg count from declaration
	lua_getglobal(L, "debug");

	// Push debug.getinfo
	lua_getfield(L, -1, "getinfo");
	lua_pushvalue(L, index);

	// Push the what string
	lua_pushstring(L, "u");

	// Call debug.getinfo(func, "u")
	lua_call(L, 2, 1);

	// Get nparams from the result
	lua_getfield(L, -1, "nparams");
	
	// Get argc
	int result = lua_tointeger(L, -1);
	
	// Cleanup stack
	lua_pop(L, 3);
	
	return result;
}

static int lu5_call(lua_State *L) {
	// Create the instance table
	lua_newtable(L); 
	
	// Set the class table as the metatable of the instance
	lua_pushvalue(L, 1); 
	lua_setmetatable(L, -2);

	// Get the 'init' method from the class table
	lua_getfield(L, 1, "init");
	if (!lua_isfunction(L, -1)) {
		luaL_error(L, "class does not have an 'init' method");
		return 0;
	}

	// Check if arg count matches
	int declaration_argc = lu5_get_declaration_argc(L, -3);
	int caller_argc = lua_gettop(L)-2;
	
	if (declaration_argc != caller_argc) {
		LU5_ERROR("Expected %i arguments in constructor, recieved %i", declaration_argc-1, caller_argc-1);
		lua_pushvalue(L, -1);
		return 1;
	}

	// Prepare to call 'init'
	lua_pushvalue(L, -2);  // Push the instance (newly created table)

	// Push all arguments from the into the 'init' call
	for (int i = 2; i <= declaration_argc; i++) {
		lua_pushinteger(L, lua_tointeger(L, i));
	}

	// Call 'init'
	if (lua_pcall(L, declaration_argc, 1, 0) != LUA_OK) {
		luaL_error(L, lua_tostring(L, -1));
		lua_pop(L, 1);  
		return 0;
	}

	// Return the new instance
	return 1;
}

int lu5_class(lua_State *L) {
	// Get the class name
	const char *name = luaL_checkstring(L, 1);
	
	// Create class table
	lua_newtable(L);

	// Set class name in class table for possible use
	lua_pushstring(L, name);
	lua_setfield(L, -2, "__name");

	// Set __index to itself
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");

	// Set new metamethod in the metatable
	lua_newtable(L);
	lua_pushcfunction(L, lu5_call);
	lua_setfield(L, -3, "new");
	
	// set the new table as its own metatable
	lua_setmetatable(L, -2);

	return 1; // Return new class
}
