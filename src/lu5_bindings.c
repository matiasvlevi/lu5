#include "lu5_bindings.h"

#include "bindings/events.h"
#include "bindings/io.h"
#include "bindings/setting.h"
#include "bindings/window.h"
#include "bindings/shapes.h"

#include "lu5_defs.h"

void lu5_update_dynamic_variables(lua_State *L, GLFWwindow *window) { 
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    int mouseIsPressed = glfwGetMouseButton(window, 0);

    LUA_ADD_CONST_NUMBER_GLOBAL(L, mouseX);
    LUA_ADD_CONST_NUMBER_GLOBAL(L, mouseY);

    LUA_ADD_CONST_BOOL_GLOBAL(L, mouseIsPressed);
}

static void lu5_register_constants(lua_State *L) 
{
    LUA_ADD_NUMBER_GLOBAL(L, "LEFT_ARROW",  263);
    LUA_ADD_NUMBER_GLOBAL(L, "RIGHT_ARROW", 262);
    LUA_ADD_NUMBER_GLOBAL(L, "UP_ARROW",    265);
    LUA_ADD_NUMBER_GLOBAL(L, "DOWN_ARROW",  264);
    LUA_ADD_NUMBER_GLOBAL(L, "ENTER",       257);
    LUA_ADD_NUMBER_GLOBAL(L, "BACKSPACE",   259);
}

void lu5_register_symbols(lua_State *L) 
{
    LUA_ADD_FUNCTION(L, print);

    LUA_ADD_FUNCTION(L, createWindow);
    LUA_ADD_FUNCTION(L, background);

    LUA_ADD_FUNCTION(L, isKeyDown);
    
	LUA_ADD_FUNCTION(L, fill);
	LUA_ADD_FUNCTION(L, noFill);
	LUA_ADD_FUNCTION(L, stroke);
	LUA_ADD_FUNCTION(L, noStroke);
    LUA_ADD_FUNCTION(L, strokeWeight);    

	LUA_ADD_FUNCTION(L, point);
    LUA_ADD_FUNCTION(L, circle);
    LUA_ADD_FUNCTION(L, ellipse);
    LUA_ADD_FUNCTION(L, square); 
    LUA_ADD_FUNCTION(L, rect); 
	LUA_ADD_FUNCTION(L, quad);
    LUA_ADD_FUNCTION(L, line);
	LUA_ADD_FUNCTION(L, triangle);
	LUA_ADD_FUNCTION(L, text);
	LUA_ADD_FUNCTION(L, arc);

	lu5_register_constants(L);
}
