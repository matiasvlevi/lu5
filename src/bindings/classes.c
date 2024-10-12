#include "classes.h"

#include "../lu5_error.h"
#include "../lu5_types.h"

#include <lauxlib.h>

/**
 * Get the number of arguments based on a function declaration 
 * 
 * @param L The lua state
 *
 * @return int The number of arguments
 */
static int lu5_get_declaration_argc(lua_State *L, int index) 
{
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

static int lu5_new(lua_State *L) 
{
	// Create the instance table
	lua_newtable(L); 
	
	// Set the class table as the metatable of the instance
	lua_pushvalue(L, 1);
	lua_setmetatable(L, -2);

		// Get the 'init' method from the class table
	lua_pushstring(L, "init");
	lua_rawget(L, 1);
	if (!lua_isfunction(L, -1)) {
		luaL_error(L, "class does not have an 'init' method");
		return 0;
	}

	int declaration_argc = lu5_get_declaration_argc(L, -3);
	int caller_argc = lua_gettop(L)-2;


	// Argument validation
	if (declaration_argc != caller_argc) {
		LU5_ERROR("Expected %i arguments in constructor, recieved %i", declaration_argc-1, caller_argc-1);
		
		lua_pushnil(L);
		return 1;
	}

	// Prepare to call 'init'
	lua_pushvalue(L, -2);

	// Push all arguments into the 'init' call
	for (int i = 2; i <= caller_argc; i++) {
		lua_pushvalue(L, i);
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


static int lu5_class_index(lua_State *L) {
	// Stack: [instance, key]

	// Try to get the value from the instance table
	lua_pushvalue(L, 2); // Push the key
	lua_rawget(L, 1);	// Raw get to avoid metamethod call again
	if (!lua_isnil(L, -1)) {
		// Return the value found
		return 1;	   
	}
	lua_pop(L, 1);

	// Get the metatable
	if (!lua_getmetatable(L, 1)) {
		lua_pushnil(L);
		return 1;
	}

	// Try to get the value from the class table
	lua_pushvalue(L, 2); // Push the key
	lua_rawget(L, -2);   // Raw get to avoid metamethod call again
	lua_remove(L, -2);   // Remove metatable from the stack

	return 1;			// Return the value (or nil)
}

static int lu5_class_newindex(lua_State *L) {
	// Stack: [instance, key, value]

	lua_pushvalue(L, 2);  // Push the key
	lua_pushvalue(L, 3);  // Push the value
	lua_rawset(L, 1);	 // Set instance[key] = value

	return 0;
}

int lu5_class(lua_State *L) 
{
	// Get the class name
	const char *name = lu5_assert_string(L, 1, "class");
	
	// Create class table
	luaL_newmetatable(L, name);

	// Set the __index and __newindex metamethods
	lua_pushcfunction(L, lu5_class_index);
	lua_setfield(L, -2, "__index");
	
	lua_pushcfunction(L, lu5_class_newindex);
	lua_setfield(L, -2, "__newindex");

	// Set class name in class table for possible use
	lua_pushstring(L, name);
	lua_setfield(L, -2, "__name");

	lua_pushcfunction(L, lu5_new);
	lua_setfield(L, -2, "new");

	return 1;
}