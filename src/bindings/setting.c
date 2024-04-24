#include "setting.h"

#include "../window.h"

int strokeWeight(lua_State *L) 
{
    double weight = lua_tonumber(L, 1);

    glLineWidth(weight);

    lu5.style.strokeWeight = weight;

    return 0;
}

int fill(lua_State *L) 
{
    GET_COLOR_FROM_LUA_ARGS(L);

    glColor4ub(r, g, b, a);

    return 0;
}
