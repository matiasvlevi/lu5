#ifndef __LU5_EVENTS_H__
#define __LU5_EVENTS_H__

#include <GLFW/glfw3.h>

void lu5_poll_events(GLFWwindow *window);

void lu5_register_event_callbacks(GLFWwindow *window);

#endif
