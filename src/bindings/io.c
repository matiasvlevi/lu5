#include "io.h"

#include "../lu5_print.h"

int print(lua_State *L)
{
	int argc = lua_gettop(L);
	
	// Print all arguments
	for (int i = 1; i < argc; i++) {
		lu5_print_any(L, i, 0, ' ');
	}
	lu5_print_any(L, argc, 0, '\n');

	return 0;
}
