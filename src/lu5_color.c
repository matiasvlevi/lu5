#include "lu5_color.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "lu5_logger.h"

static lu5_color lu5_hex_args_to_color(lua_State *L) 
{
    int length = luaL_len(L, 1);
    const char* hex_str = luaL_checkstring(L, 1);

    // Check string format and length
    if (hex_str[0] != '#') {
        return (lu5_color)(0xFFFFFFFF);
    }

    // 3 bytes hex rgb color
    if (length == 7) {
        unsigned int rgb;

        // Parse 3 bytes of hex and skip '#'
        int parsed = sscanf(hex_str + 1, "%6x", &rgb); 
        if (parsed != 1) {
            // In case of parsing error return white
            return (lu5_color)(0xFFFFFFFF);
        }

        // Shift a byte for Alpha
        return (lu5_color)(rgb << 8);
    } 
    
    // 4 bytes hex rgba color
    if (length == 9) {
        unsigned int rgba;

        // Parse 4 bytes of hex and skip '#'
        int parsed = sscanf(hex_str + 1, "%8x", &rgba); 
        if (parsed != 1) {
            // In case of parsing error return white
            return (lu5_color)(0xFFFFFFFF);
        }

        return (lu5_color)(rgba);    
    }

    return (lu5_color)(0xFFFFFFFF);
}

static lu5_color lu5_label_args_to_color(lua_State *L)
{
    return (lu5_color)(0xFFFFFFFF);
} 

static lu5_color lu5_string_args_to_color(lua_State *L) 
{
    const char* str = luaL_checkstring(L, 1);

    // Return white if not a string
    if (str == NULL) 
        return (lu5_color)(0xFFFFFFFF);

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
    // If first argument is a number, assume rgba arguments
    if (lua_isnumber(L, 1)) 
        return lu5_rgba_args_to_color(L);

    // If first argument is string, handle string
    if (lua_isstring(L, 1)) 
        return lu5_string_args_to_color(L);    
}


