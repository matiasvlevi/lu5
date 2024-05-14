#ifndef _LU5_STATE_H_
#define _LU5_STATE_H_

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

#define LU5_SET_DEFAULT_STYLE(s)\
	(s)->strokeWeight = 1;\
	(s)->stroke = LU5_BLACK;\
	(s)->fill = LU5_WHITE;\
	(s)->fontSize = 22;\
	(s)->font_current = NULL;\

typedef struct {
	FT_Face face;
	GLuint textures[128];
} lu5_font;


// Callback function for when the window's size is changed ..
// TODO: move to new file ./src/window.h
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

typedef struct lu5_node_ {
	void *data;
	struct lu5_node_ *next;
} lu5_node;

void lu5_list_push(lu5_node **head, void *data, size_t data_size);

void lu5_list_iter(lu5_node *node, void (*ptr)(void*));
void lu5_list_iter_close(lu5_node *node, void (*ptr)(void*));

typedef struct {
	lu5_color fill;
	lu5_color stroke;
	double strokeWeight;
	double fontSize;

	// current font reference
	lu5_font *font_current;
} lu5_style_setting_t;

/**
 * @brief Core lu5 state
 */
typedef struct {

	lua_State *L;

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

			int keypress_queue_count;
			int keypress_queue[MAX_KEY_PRESSED_QUEUE];
		} keyboard;

	} input;

	struct env {
		double now_time;
		double last_time;
		double last_frame_time;
		double delta_time;
		int target_framerate;
	} env;

} lu5_State;

void lu5_close(lu5_State *l5);

extern lu5_State lu5;

#endif
