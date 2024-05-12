#include "keyboard.h"

#include "../lu5_state.h"

int isKeyDown(lua_State *L) 
{
	int key = -1;
	if (lua_isnumber(L, 1)) {
		key = lua_tointeger(L, 1);
	} else {
		const char *str = lua_tostring(L, 1);
		if (str != NULL) {
			// Convert to keyCode value
			key = ((int)str[0]) - ((int)' ');
		}
	}

	bool down = false;

	if ((key > 0) && (key < MAX_KEYBOARD_KEYS))
	{
		down = (lu5.input.keyboard.current_keys[key] == 1);
	}

	lua_pushboolean(L, down);
	return 1;
}

