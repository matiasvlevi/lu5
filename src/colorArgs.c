#include "colorArgs.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <raylib.h>

Color rgbColorFromLuaArguments(lua_State *L) {
    int r = lua_tonumber(L, 1);

    int g = r; /* Default is 1 */
    if(lua_gettop(L) > 1) {
        g = lua_tonumber(L, 2);
    }

    int b = r; /* Default is 1 */
    if(lua_gettop(L) > 2) {
        b = lua_tonumber(L, 3);
    }

    int a = 0xFF; /* Default is 1 */
    if(lua_gettop(L) > 3) {
        a = lua_tonumber(L, 4);
    }

    return (Color){ r, g, b, a };
}


