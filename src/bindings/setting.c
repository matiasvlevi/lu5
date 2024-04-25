#include "setting.h"

#include <lauxlib.h>

#include "../lu5_state.h"

int strokeWeight(lua_State *L) 
{
    double weight = lua_tonumber(L, 1);

    glLineWidth(weight);

    lu5.style.strokeWeight = weight;

    return 0;
}

int fill(lua_State *L) 
{
    lu5_color color = lu5_args_to_color(L);

    glColor4ub(color.r, color.g, color.b, color.a);

    return 0;
}

int noFill(lua_State *L) 
{
    luaL_error(L, "TODO: Implement noFill");

    return 0;
}

int stroke(lua_State *L) 
{
    lu5_color color = lu5_args_to_color(L); 

    luaL_error(L, "TODO: Implement stroke, stroke(%f, %f, %f, %f)", color.r, color.g, color.b, color.a);

    return 0;
}

int noStroke(lua_State *L) 
{
    luaL_error(L, "TODO: Implement noStroke");

    return 0;
}
