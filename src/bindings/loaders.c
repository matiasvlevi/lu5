#include "loaders.h"
#include <lauxlib.h>

#include "../lu5_logger.h"
#include "../lu5_font.h"

int loadFont(lua_State *L) {
	
	const char *font_path = lua_tostring(L, 1);

	if (!font_path) {
		// If default font is defined
		if (lu5.font_count >= 1) {
			LU5_WARN_TRACE(L, "Returning default font, Expected first argument to be a string");
			
			// return default font
			lua_pushinteger(L, 0);
			return 1;
		} else {

			// Throw
			luaL_error(L, "Expected first argument to be a string");
			return 0;
		}

	}

	int fontId;
	lu5_loadfont_err err = lu5_load_font(&lu5, &fontId, font_path, false);
	if (err == LU5_LOADFONT_NONE) {
		// Return the fontId
		lua_pushinteger(L, fontId);
		return 1;
	}

	// Throw
	switch(err) {
		case LU5_LOADFONT_NOT_FOUND: {
			// If default font is defined
			if (lu5.font_count >= 1) {
				LU5_WARN_TRACE(L, "Could not find '%s' font, returning default font", font_path);
				
				// return default font
				lua_pushinteger(L, 0);
				return 1;
			} else {

				// Throw
				luaL_error(L, "Could not find '%s' font", font_path);
				return 0;
			}
			break;
		}
		case LU5_LOADFONT_MAX: {
			luaL_error(L, "Could not load '%s' since we cannot load more than %d fonts", font_path, MAX_LOADED_FONTS);
			break;
		}
		case LU5_LOADFONT_UNKNOWN: {		
			luaL_error(L, "Could not find font '%s'", font_path);
			break;
		}
		case LU5_LOADFONT_UNKNOWN_FORMAT: {
			luaL_error(L, "Unknown file format for '%s'", font_path);
			break;
		}
		case LU5_LOADFONT_NO_MEM: {
			luaL_error(L, "No memory left to load '%s'", font_path);
			break;
		}
		case LU5_LOADFONT_NONE: break;
	}

	// Return default font
	lua_pushinteger(L, 0);
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
