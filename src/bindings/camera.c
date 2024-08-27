#include "camera.h"

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

#include "../lu5_state.h"
#include "../lu5_logger.h"

#include <stdlib.h>

#define MOUSE_SENSIBILITY 0.3f
#define ZOOM_SENSIBILITY 0.18f

int orbitControl(lua_State *L) 
{
    if (lu5.orbit == NULL) 
    {
        lu5_orbit *orbit = (lu5_orbit*)malloc(sizeof(lu5_orbit));
        orbit->dragging = false;
        orbit->radius = 600.0f;
        
        orbit->camera_angle_x = 0.0f;
        orbit->camera_angle_y = 0.0f;

        orbit->angular_velocity_x = 0.0f;
        orbit->angular_velocity_y = 0.0f;
        
        orbit->previous_mouse_x = 0.0f;
        orbit->previous_mouse_y = 0.0f;

        lu5.orbit = orbit;
    }

    double mouseX, mouseY;
    glfwGetCursorPos(lu5.window, &mouseX, &mouseY);

    // Drag mechanics
    if (lu5.input.mouse.actions[0] == GLFW_PRESS) {
        if (!lu5.orbit->dragging) {
            lu5.orbit->dragging = true;
            lu5.orbit->previous_mouse_x = mouseX;
            lu5.orbit->previous_mouse_y = mouseY;
        } else {
            lua_Number deltaX = lu5.orbit->previous_mouse_x - mouseX;
            lua_Number deltaY = mouseY - lu5.orbit->previous_mouse_y;
            lu5.orbit->previous_mouse_x = mouseX;
            lu5.orbit->previous_mouse_y = mouseY;

            lu5.orbit->angular_velocity_y = deltaX * MOUSE_SENSIBILITY;
            lu5.orbit->angular_velocity_x = deltaY * MOUSE_SENSIBILITY;
        }
    } else if (lu5.input.mouse.actions[0] == GLFW_RELEASE) {
        lu5.orbit->dragging = false;
    }

    // Friction when not dragging
    if (!lu5.orbit->dragging) {
        lu5.orbit->angular_velocity_y *= 0.94f;
        lu5.orbit->angular_velocity_x *= 0.94f;
    }

    // apply velocity
    lu5.orbit->camera_angle_y += lu5.orbit->angular_velocity_y;
    lu5.orbit->camera_angle_x -= lu5.orbit->angular_velocity_x;

    lu5.orbit->radius += lu5.input.mouse.scrollY * ZOOM_SENSIBILITY;
    lu5.input.mouse.scrollY *= 0.95f;

    // Clamp radius
    lu5.orbit->radius = fmaxf(0.03f, lu5.orbit->radius);

    // Clamp pitch
    lu5.orbit->camera_angle_x = fminf( 89.0f, lu5.orbit->camera_angle_x);
    lu5.orbit->camera_angle_x = fmaxf(-89.0f, lu5.orbit->camera_angle_x);

    float x = lu5.orbit->radius * cosf(lu5.orbit->camera_angle_x * M_PI / 180.0f) * sinf(lu5.orbit->camera_angle_y * M_PI / 180.0f);
    float y = lu5.orbit->radius * sinf(lu5.orbit->camera_angle_x * M_PI / 180.0f);
    float z = lu5.orbit->radius * cosf(lu5.orbit->camera_angle_x * M_PI / 180.0f) * cosf(lu5.orbit->camera_angle_y * M_PI / 180.0f);

    glLoadIdentity();
    glScalef(-1, 1, 1);
    gluLookAt(x, y, z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    return 0;
}