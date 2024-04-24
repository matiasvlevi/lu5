#include "setting.h"

#include <lauxlib.h>

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

int noFill(lua_State *L) 
{
    luaL_error(L, "TODO: Implement noFill");

    return 0;
}

int stroke(lua_State *L) 
{
    GET_COLOR_FROM_LUA_ARGS(L);

    luaL_error(L, "TODO: Implement stroke, stroke(%f, %f, %f, %f)", r, g, b, a);

    return 0;
}

int noStroke(lua_State *L) 
{
    luaL_error(L, "TODO: Implement noStroke");

    return 0;
}
