#include "setting.h"

#include <lauxlib.h>

#include "../lu5_state.h"
#include "../lu5_font.h"

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

    lu5.style.fill = color;

    return 0;
}

int noFill(lua_State *L) 
{
    lu5.style.fill = (lu5_color){ .r=0, .g=0, .b=0, .a=0 };

    return 0;
}

int stroke(lua_State *L) 
{
    lu5_color color = lu5_args_to_color(L); 

    lu5.style.stroke = color;

    return 0;
}

int noStroke(lua_State *L) 
{
    lu5.style.stroke = (lu5_color){ .r=0, .g=0, .b=0, .a=0 };

    return 0;
}

int textSize(lua_State *L)
{
    double size = lua_tonumber(L, 1);

    FT_Set_Pixel_Sizes(face, 0, size); 
    
    lu5.style.fontSize = size;

    return 0;
}
