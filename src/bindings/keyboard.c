#include "keyboard.h"

#include "../lu5_state.h"
#include "../lu5_types.h"

int keyIsDown(lua_State *L) 
{
	lua_Integer key = -1;
	if (lua_isinteger(L, 1)) 
	{
		key = lua_tointeger(L, 1);
	} 
	else 
	{
		const char *str = lu5_assert_string(L, 1, "keyIsDown");
		if (str != NULL) {
			// Convert to keyCode value
			key = ((int)str[0]) - ((int)' ');
		}
	}

	bool down = false;

	if ((key > 0) && (key < MAX_KEYBOARD_KEYS))
	{
		down = (lu5.input.keyboard.is_down[key] == true);
	}

	lua_pushboolean(L, down);
	return 1;
}

