#ifndef _LU5_STATE_H_
#define _LU5_STATE_H_

#include <GLFW/glfw3.h>

#include <stdbool.h>

#include "lu5_style.h"
#include "lu5_logger.h"

#define MAX_MOUSE_BUTTONS 8
#define MAX_KEYBOARD_KEYS 512

typedef struct lu5_node_s lu5_node;
typedef struct lu5_font_s lu5_font;
typedef struct FT_LibraryRec_ *FT_Library;

/**
 * @brief Core lu5 state
 */
typedef struct {
	lua_State *L;

	GLFWwindow *window;

	lu5_log_level log_level; 

	// FONT
	FT_Library ft;
	lu5_font *font_default;
	lu5_node *fonts;

	// Images
	lu5_node *images;

	lu5_style_setting_t style;
	lu5_style_setting_t style_cache;

	struct input {
		struct {
			int actions[MAX_MOUSE_BUTTONS];
		} mouse;

		struct {
			int current_keys[MAX_KEYBOARD_KEYS];
			bool is_down[MAX_KEYBOARD_KEYS];
		} keyboard;

	} input;

	struct env {
		double now_time;
		double last_time;
		double last_frame_time;
		double delta_time;
		int target_framerate;
		bool restart;
	} env;

} lu5_State;

extern lu5_State lu5;

#endif
