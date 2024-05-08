#ifndef __LU5_WINDOW_H_
#define __LU5_WINDOW_H_

#define MAX_MOUSE_BUTTONS 8

#define MAX_KEYBOARD_KEYS 512
#define MAX_KEY_PRESSED_QUEUE 16

#include <lua.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>

#include "lu5_color.h"
#include "lu5_logger.h"

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif

#include <ft2build.h>
#include FT_FREETYPE_H

#define MAX_LOADED_FONTS 16
typedef struct {
	FT_Face face;
	GLuint textures[128];
} lu5_font;

typedef struct {
	struct {
		struct {
			int actions[MAX_MOUSE_BUTTONS];
		} mouse;

		struct {
			int current_keys[MAX_KEYBOARD_KEYS];

			int keypress_queue_count;
			int keypress_queue[MAX_KEY_PRESSED_QUEUE];
		} keyboard;

	} input;

	struct {
		lu5_color fill;
		lu5_color stroke;
		double strokeWeight;
		double fontSize;
		int fontId;
	} style;

	struct {
		double now_time;
		double last_time;
		double last_frame_time;
		double delta_time;
		int target_framerate;
	} env;

	lu5_log_level log_level; 

	FT_Library ft;
	lu5_font *fonts[MAX_LOADED_FONTS];
	int font_count;

	lua_State *L;

} lu5_State;

extern lu5_State lu5;

// Callback function for when the window's size is changed
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


#endif
