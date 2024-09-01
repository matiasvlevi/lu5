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
typedef struct lu5_orbit_s lu5_orbit;
typedef struct FT_LibraryRec_ *FT_Library;

/**
 * @brief Core lu5 state
 */
typedef struct {
	lua_State *L;
	bool debug;

	GLFWwindow *window;
	float width;
	float height;
	int depth_mode;

	lu5_log_level log_level; 

	// FONT
	FT_Library ft;
	lu5_font *font_default;
	lu5_node *fonts;

	// Images
	lu5_node *images;

	// Models
	lu5_node *models;

	lu5_style_setting_t style;
	lu5_style_setting_t style_cache;

	struct input {
		struct {
			int actions[MAX_MOUSE_BUTTONS];
			lua_Number pmouseX;
			lua_Number pmouseY;
			float scrollY;
		} mouse;

		struct {
			int current_keys[MAX_KEYBOARD_KEYS];
			bool is_down[MAX_KEYBOARD_KEYS];
		} keyboard;

	} input;

	struct env {
		lua_Number now_time;
		lua_Number last_time;
		lua_Number last_frame_time;
		lua_Number delta_time;
		int target_framerate;
		bool restart;
	} env;

	lu5_orbit *orbit;

} lu5_State;

extern lu5_State lu5;

#endif
