#ifndef _LU5_STATE_H_
#define _LU5_STATE_H_

#include "lu5_window.h"
#include <stdbool.h>
#include <time.h>

#include "lu5_style.h"
#include "lu5_error.h"

#define MAX_MOUSE_BUTTONS 8
#define MAX_KEYBOARD_KEYS 512
#define LU5_MAX_STYLE_STACK 64

typedef struct lu5_node_s lu5_node;
typedef struct lu5_font_s lu5_font;
typedef struct lu5_orbit_s lu5_orbit;
typedef struct FT_LibraryRec_ *FT_Library;
 
/**
 * @brief Core lu5 state
 */
typedef struct lu5_State_s {
	lua_State *L;

	struct env {
		// This is at an 8 byte offset for 
		// convenience in WASM
		int target_framerate;

		// Time & Loop
		lua_Number now_time;
		lua_Number last_time;
		lua_Number last_frame_time;
		float delta_time;
		bool restart;
		clock_t restart_time;
	} env;

	// Debug mode
	bool debug;

	// Window related
	lu5_window *window;
	float width;
	float height;
	int depth_mode;
	bool loop;

	//
	lu5_log_level log_level; 

	// FONT
	FT_Library ft;
	lu5_font *font_default;
	lu5_node *fonts;

	// Images
	lu5_node *images;

	// Models
	lu5_node *models;

	// Style stack (fill, stroke, font sizes, etc)
	lu5_style_setting *style_stack[LU5_MAX_STYLE_STACK];
	size_t style_stack_len;

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

	// Orbit state for `orbitControl`
	lu5_orbit *orbit;

} lu5_State;

extern lu5_State lu5;

/**
 * Init the lu5 state
 *
 * @param l5 A preallocated lu5_State pointer
 */
void lu5_init_state(lu5_State *l5);

#endif
