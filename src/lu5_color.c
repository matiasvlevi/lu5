#include "lu5_color.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <string.h>

#include "lu5_logger.h"

lu5_labeled_color lu5_known_colors[LU5_COLOR_COUNT] = {
    {
        .name="white",
        .color= LU5_RGBA(255, 255, 255, 255)
    },
    {
        .name="black",
        .color= LU5_RGBA(0, 0, 0, 255)
    },
    {
        .name="grey",
        .color= LU5_RGBA(51, 51, 51, 255)
    },
    {
        .name="red",
        .color= LU5_RGBA(245, 70, 10, 255)
    },
    {
        .name="pink",
        .color= LU5_RGBA(255, 25, 180, 255)
    },
    {
        .name="magenta",
        .color= LU5_RGBA(210, 81, 255, 255)
    },
    {
        .name="blue",
        .color= LU5_RGBA(10, 70, 245, 255)
    },
    {
        .name="green",
        .color= LU5_RGBA(10, 245, 70, 255)
    },
    {
        .name="yellow",
        .color= LU5_RGBA(205, 225, 36, 255)
    },
    {
        .name="orange",
        .color= LU5_RGBA(255, 125, 16, 255)
    },
    {
        .name="cyan",
        .color= LU5_RGBA(20, 200, 255, 255)
    }
};

void lu5_register_colors(lua_State *L) 
{
    lua_newtable(L);

    for (int i = 0; i < LU5_COLOR_COUNT; i++) {
        lua_pushnumber(L, i+1);

        lua_pushstring(L, lu5_known_colors[i].name);

        lua_settable(L, -3);
    }

    lua_setglobal(L, "colors");
}

static lu5_color lu5_hex_args_to_color(lua_State *L) 
{
    int length = luaL_len(L, 1);
    const char* hex_str = luaL_checkstring(L, 1);

    // Check string format and length
    if (hex_str[0] != '#') {
        LU5_WARN_TRACE(L, "Expected hexadecimal color string");
        return LU5_WHITE;
    }

    // 3 bytes hex rgb color
    if (length == 7) {
        unsigned int rgb;

        // Parse 3 bytes of hex and skip '#'
        int parsed = sscanf(hex_str + 1, "%6x", &rgb); 
        if (parsed != 1) {
            // In case of parsing error return white
            LU5_WARN_TRACE(L, "Failed to parse hexadecimal string");
            return LU5_WHITE;
        }

        // Shift a byte and set Alpha to max
        return (lu5_color)((rgb << 8) | 0xFF);
    } 
    
    // 4 bytes hex rgba color
    if (length == 9) {
        unsigned int rgba;

        // Parse 4 bytes of hex and skip '#'
        int parsed = sscanf(hex_str + 1, "%8x", &rgba); 
        if (parsed != 1) {
            // In case of parsing error return white
            LU5_WARN_TRACE(L, "Failed to parse hexadecimal string");
            return LU5_WHITE;
        }

        return (lu5_color)(rgba);    
    }

    LU5_WARN_TRACE(L, "Expected length of hexadecimal string to be either of 7 or 9 characters");
    return LU5_WHITE;
}


static lu5_color lu5_label_args_to_color(lua_State *L)
{
    const char *label = luaL_checkstring(L, 1);
    if (label == NULL) {
        LU5_WARN_TRACE(L, "Expected a string for first argument");
        return LU5_WHITE;
    }
     
    for (int i = 0; i < LU5_COLOR_COUNT; i++) {
        if (strcmp(label, lu5_known_colors[i].name) == 0) {
            return lu5_known_colors[i].color;
        }
    }

    LU5_WARN_TRACE(L, "'%s' did not match any known colors", label);
    return LU5_WHITE;
} 

static lu5_color lu5_string_args_to_color(lua_State *L) 
{
    int arg_length = lua_gettop(L);

    if (arg_length != 1) {
        LU5_WARN_TRACE(L, "Found %i arguments but expected 1 string argument", arg_length);
        return LU5_WHITE;
    }

    const char* str = luaL_checkstring(L, 1);

    // Return white if not a string
    if (str == NULL) {
        LU5_WARN_TRACE(L, "Could not get string argument");
        return LU5_WHITE;
    }

    // if first char is hex prefix, handle hex
    if (str[0] == '#') {
        return lu5_hex_args_to_color(L);
    } else {
        return lu5_label_args_to_color(L);
    }
}

static lu5_color lu5_rgba_args_to_color(lua_State *L)
{
    int length = lua_gettop(L);

    if (length == 0 || length > 4) {
        LU5_WARN_TRACE(L, "Found %i arguments but expected between 1 to 4 number arguments", length);
        return LU5_WHITE;
    }

    if (length == 1) {
        uint8_t r = lua_tointeger(L, 1) & 0xFF;
        return (lu5_color){ .r=r, .g=r, .b=r, .a=0xFF };
    }

    if (length == 2) {
        uint8_t r = lua_tointeger(L, 1) & 0xFF;
        uint8_t a = lua_tointeger(L, 2) & 0xFF;

        return (lu5_color){ .r=r, .g=r, .b=r, .a=a };
    }

    if (length == 3) {
        uint8_t r = lua_tointeger(L, 1) & 0xFF;
        uint8_t g = lua_tointeger(L, 2) & 0xFF;
        uint8_t b = lua_tointeger(L, 3) & 0xFF;  

        return (lu5_color){ .r=r, .g=g, .b=b, .a=0xFF };
    }

    uint8_t r = lua_tointeger(L, 1) & 0xFF;
    uint8_t g = lua_tointeger(L, 2) & 0xFF;
    uint8_t b = lua_tointeger(L, 3) & 0xFF; 
    uint8_t a = lua_tointeger(L, 4) & 0xFF; 

    return (lu5_color){ .r=r, .g=g, .b=b, .a=a };
}

lu5_color lu5_args_to_color(lua_State *L) 
{
    int type = lua_type(L, 1);

    switch(type) {
        case LUA_TNUMBER:
            return lu5_rgba_args_to_color(L);
            break;

        case LUA_TSTRING:
            return lu5_string_args_to_color(L);    
            break;

        default: {
            const char* typename = lua_typename(L, type);


            LU5_WARN_TRACE(L, "Expected hex color string or RGB number values, but got %s", typename);
            return LU5_WHITE;
            break;
        }
    }

}


