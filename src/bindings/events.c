#include "events.h"

#include "../window.h"

int isKeyDown(lua_State *L) 
{
    int key = lua_tointeger(L, 1);

    bool down = false;

    if ((key > 0) && (key < MAX_KEYBOARD_KEYS))
    {
        down = (lu5.input.keyboard.current_keys[key] == 1);
    }

    lua_pushboolean(L, down);
    return 1;
}

