#ifndef __LU5_WINDOW_H_
#define __LU5_WINDOW_H_

#define MAX_MOUSE_BUTTONS 8

#define MAX_KEYBOARD_KEYS 512
#define MAX_KEY_PRESSED_QUEUE 16

#include <lua.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>

#include "lu5_color.h"

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
    } style;
    
    lua_State *L;

} lu5_state;

extern lu5_state lu5;

// Callback function for when the window's size is changed
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


#endif
