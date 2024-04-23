#ifndef __LU5_EVENTS_H__
#define __LU5_EVENTS_H__

#include <GLFW/glfw3.h>

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void lu5_poll_events();

#endif
