#include "loaders.h"
#include <lauxlib.h>

#include "../lu5_logger.h"
#include "../lu5_font.h"

int loadFont(lua_State *L) {
	
	const char *str = luaL_checkstring(L, 1);
	if (!str) {
		luaL_error(L, "Expected first argument to be a string");

		// Default font
		lua_pushinteger(L, 0);
		return 1;
	}


	int fontId = 0;
	lu5_loadfont_err err = LOADFONT_NONE;
	if ((err = lu5_load_font(&lu5, str, &fontId)) != 0) {
		switch(err) {
			case LOADFONT_UNKNOWN: {		
				luaL_error(L, "Could not find font '%s'", str);
				break;
			}
			case LOADFONT_UNKNOWN_FORMAT: {
				luaL_error(L, "Unknown file format for '%s'", str);
				break;
			}
			case LOADFONT_MAX: {
				luaL_error(L, "Cannot load more than %d fonts", MAX_LOADED_FONTS);
				break;
			}
			default: break;
		}
		// Default font
		lua_pushinteger(L, 0);
		return 1;
	}

	// Return the fontId
	lua_pushinteger(L, fontId);
	return 1;
}

int loadImage(lua_State *L) {
	return 0;
}

int loadJSON(lua_State *L) {
	return 0;
}

int loadCSV(lua_State *L) {
	return 0;
}

int loadText(lua_State *L) {
	return 0;
}
