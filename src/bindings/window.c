
#include "window.h"

#include "../lu5_font.h"
#include "../lu5_bindings.h"
#include "../lu5_state.h"
#include "../lu5_types.h"

#include <stdio.h>
#include <stdlib.h>
#include <lauxlib.h>

#include <math.h>
#include "../lu5_window.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../platform/stb/stb_image_write.h"

int createWindow(lua_State *L) 
{
	int argc = lua_gettop(L);
	if (argc != 2 && argc != 3) {
		luaL_error(L, "Expected 2 or 3 arguments, width, height and mode");
		return 0;
	}

	lua_Integer width = lu5_assert_integer(L, 1, "createWindow");
	lua_Integer height = lu5_assert_integer(L, 2, "createWindow");

	lua_Integer depth_mode = LU5_GL2D;
	if (lua_isinteger(L, 3)) {
		depth_mode = lua_tointeger(L, 3);
	}

	//
	lua_getglobal(L, "sketch");
	const char *sketch_path = luaL_checkstring(L, -1);
	if (sketch_path == NULL) {
		LU5_WARN("The 'sketch' file path was altered, the window cannot find a name");
	};

	#ifndef LU5_WASM
	// Add prefix to window title
	int len = luaL_len(L, -1);
	char* window_title = malloc(len + 10);
	sprintf(window_title, "[lu5]: %s", sketch_path);

	// Create window
	lu5_window* window = lu5_create_lu5_window(L,
		width, height, 
		window_title,
		depth_mode
	);

	// Window title was copied in the window
	free(window_title);

	if (window == NULL) {
		luaL_error(L, "Something went wrong when creating the window");
		return 0;
	};

	// Set glfw window in global scope 
	lua_pushlightuserdata(L, window);
	lua_setglobal(L, "window");
	#else
	lu5_create_lu5_window(L,
		width, height, 
		"lu5",
		depth_mode
	);
	#endif

	// Expose window width & height to user
	lua_pushnumber(L, width);
	lua_setglobal(L, LU5_WIDTH);

	lua_pushnumber(L, height);
	lua_setglobal(L, LU5_HEIGHT);


	lu5.width = width;
	lu5.height = height;
	
	lu5_load_default_font(&lu5);

	return 0;
}

int saveWindow(lua_State *L)
{
	// TODO: pass window as first arguement, and path as second.
	const char* path = lu5_assert_string(L, 1, "saveWindow");

	#ifndef LU5_WASM
	int width, height;
	glfwGetWindowSize(lu5.window, &width, &height);
	
    // Allocate memory to store the pixel data
    unsigned char *pixels = (unsigned char *)malloc(4 * width * height);
    if (!pixels) {
        luaL_error(L, "Failed to allocate memory for pixels\n");
        return 0;
    }

    // Read pixels from the current framebuffer
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    // the image vertically
    int stride = width * 4;
    unsigned char *flipped_pixels = (unsigned char *)malloc(4 * width * height);
    if (!flipped_pixels) {
        luaL_error(L, "Failed to allocate memory for flipped pixels\n");
        free(pixels);
        return 0;
    }

    for (int row = 0; row < height; row++) {
        memcpy(flipped_pixels + row * stride, pixels + (height - row - 1) * stride, stride);
    }

    free(pixels);

   // Determine the image file format by checking the file extension
    const char *ext = strrchr(path, '.');
    if (!ext) {
        luaL_error(L, "No file extension found\n");
    } else if (strcmp(ext, ".png") == 0) {
        if (!stbi_write_png(path, width, height, 4, flipped_pixels, stride)) {
            luaL_error(L, "Failed to write PNG image to file\n");
        }
    } else if (strcmp(ext, ".bmp") == 0) {
        if (!stbi_write_bmp(path, width, height, 4, flipped_pixels)) {
            luaL_error(L, "Failed to write BMP image to file\n");
        }
    } else if (strcmp(ext, ".jpg") == 0) {
        if (!stbi_write_jpg(path, width, height, 4, flipped_pixels, 100)) {
            luaL_error(L, "Failed to write JPEG image to file\n");
        }
    } else {
        luaL_error(L, "Unsupported file extension: %s\n, can be either png, bmp or jpg", ext);
    }
	
    free(flipped_pixels);

	#else
	// TODO: WASM
	LU5_WARN("saveWindow is not yet supported in lu5-wasm");
	#endif

	return 0;
}



int frameRate(lua_State *L) 
{
	if (lua_gettop(L) > 0) 
	{
		lu5.env.target_framerate = lu5_assert_integer(L, 1, "frameRate");
		return 0;
	} 
	else 
	{
		#ifndef LU5_WASM
			// Return the current framerate
			if (lu5.env.target_framerate == -1) 
				// For free frame rates
				lua_pushnumber(L, roundf(1000.0 / (lu5.env.delta_time))/1000.0);
			else 
				// For fixed frame rates
				lua_pushnumber(L, roundf(1000.0 / (lu5.env.now_time - lu5.env.last_frame_time))/1000.0);
			
		#else // LU5_WASM
			lua_pushnumber(L, roundf(lu5.env.framerate_avg));
		#endif
		return 1;
	}
}

int noLoop(lua_State *L)
{
	lu5_noLoop();

	return 0;
}

int loop(lua_State *L)
{
	lu5_loop();

	return 0;
}