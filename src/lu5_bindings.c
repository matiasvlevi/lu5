#include "lu5_bindings.h"

#include "bindings/classes.h"
#include "bindings/window.h"
#include "bindings/setting.h"
#include "bindings/lu5_math.h"
#include "bindings/io.h"
#include "bindings/shapes.h"
#include "bindings/mouse.h"
#include "bindings/keyboard.h"
#include "bindings/typography.h"
#include "bindings/image.h"

void lu5_update_dynamic_variables(lu5_State *l5, GLFWwindow *window) 
{
	
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(l5->L, LU5_MOUSE_X, mouseX);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(l5->L, LU5_MOUSE_Y, mouseY);

	int mouseIsPressed = glfwGetMouseButton(window, 0);
	LUA_ADD_BOOL_GLOBAL_BY_NAME(l5->L, LU5_MOUSE_IS_PRESSED, mouseIsPressed);

	if (l5->env.target_framerate == -1) {
		// For free frame rates
		LUA_ADD_NUMBER_GLOBAL_BY_NAME(l5->L, LU5_DELTA_TIME, l5->env.delta_time);
	} else {
		// For fixed frame rates
		LUA_ADD_NUMBER_GLOBAL_BY_NAME(l5->L, LU5_DELTA_TIME, (lu5.env.now_time - lu5.env.last_frame_time));
	}
}


static void lu5_register_constants(lua_State *L) 
{
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "LEFT_ARROW" , LU5_KEY_LEFT_ARROW);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "RIGHT_ARROW", LU5_KEY_RIGHT_ARROW);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "UP_ARROW"   , LU5_KEY_UP_ARROW);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "DOWN_ARROW" , LU5_KEY_DOWN_ARROW);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "ENTER"      , LU5_KEY_ENTER);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "BACKSPACE"  , LU5_KEY_BACKSPACE);

	LUA_ADD_INTEGER_GLOBAL_BY_NAME(L, "POINTS"        , GL_POINTS);
	LUA_ADD_INTEGER_GLOBAL_BY_NAME(L, "QUADS"         , GL_QUADS);
	LUA_ADD_INTEGER_GLOBAL_BY_NAME(L, "LINES"         , GL_LINES);
	LUA_ADD_INTEGER_GLOBAL_BY_NAME(L, "LINE_STRIP"    , GL_LINE_STRIP);
	LUA_ADD_INTEGER_GLOBAL_BY_NAME(L, "LINE_LOOP"     , GL_LINE_LOOP);
	LUA_ADD_INTEGER_GLOBAL_BY_NAME(L, "TRIANGLES"     , GL_TRIANGLES);
	LUA_ADD_INTEGER_GLOBAL_BY_NAME(L, "TRIANGLE_STRIP", GL_TRIANGLE_STRIP);
	LUA_ADD_INTEGER_GLOBAL_BY_NAME(L, "TRIANGLE_FAN"  , GL_TRIANGLE_FAN);
	LUA_ADD_INTEGER_GLOBAL_BY_NAME(L, "QUAD_STRIP"    , GL_QUAD_STRIP);

	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "TWO_PI"    , LU5_TWO_PI);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "PI"        , LU5_PI);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "HALF_PI"   , LU5_HALF_PI);
	LUA_ADD_NUMBER_GLOBAL_BY_NAME(L, "QUARTER_PI", LU5_QUARTER_PI);
}

void lu5_register_symbols(lua_State *L) 
{
	LUA_ADD_STRING_GLOBAL_BY_NAME(L, "VERSION", LU5_VERSION);

	// IO
	LUA_ADD_FUNCTION(L, print);
	LUA_ADD_FUNCTION(L, loadStrings);
	LUA_ADD_FUNCTION(L, loadText);

	// Window
	LUA_ADD_FUNCTION(L, createWindow);
	LUA_ADD_FUNCTION(L, background);
	LUA_ADD_FUNCTION(L, frameRate);

	// Input
	LUA_ADD_FUNCTION(L, keyIsDown);

	// Setting
	LUA_ADD_FUNCTION(L, push);
	LUA_ADD_FUNCTION(L, pop);
	LUA_ADD_FUNCTION(L, fill);
	LUA_ADD_FUNCTION(L, noFill);	
	LUA_ADD_FUNCTION(L, stroke);
	LUA_ADD_FUNCTION(L, noStroke);
	LUA_ADD_FUNCTION(L, strokeWeight);    

	LUA_ADD_FUNCTION(L, beginShape);
	LUA_ADD_FUNCTION(L, vertex);
	LUA_ADD_FUNCTION(L, endShape);

	// Shapes
	LUA_ADD_FUNCTION(L, circle);
	LUA_ADD_FUNCTION(L, ellipse);
	LUA_ADD_FUNCTION(L, square); 
	LUA_ADD_FUNCTION(L, rect); 
	LUA_ADD_FUNCTION(L, quad);
	LUA_ADD_FUNCTION(L, line);
	LUA_ADD_FUNCTION(L, triangle);
	LUA_ADD_FUNCTION(L, point);
	LUA_ADD_FUNCTION(L, arc);

	// Typography
	LUA_ADD_FUNCTION(L, loadFont);
	LUA_ADD_FUNCTION(L, text);
	LUA_ADD_FUNCTION(L, textSize);
	LUA_ADD_FUNCTION(L, textFont);

	// Images
	LUA_ADD_FUNCTION(L, image);
	LUA_ADD_FUNCTION(L, loadImage);

	// OOP
	LUA_ADD_FUNCTION_BY_NAME(L, "class", lu5_class);

	// MATH
	LUA_ADD_FUNCTION_BY_NAME(L,"randomSeed", lu5_randomSeed);
	LUA_ADD_FUNCTION_BY_NAME(L,    "random", lu5_random);
	LUA_ADD_FUNCTION_BY_NAME(L,     "round", lu5_round);
	LUA_ADD_FUNCTION_BY_NAME(L,      "ceil", lu5_ceil);
	LUA_ADD_FUNCTION_BY_NAME(L,     "floor", lu5_floor);
	LUA_ADD_FUNCTION_BY_NAME(L,       "sin", lu5_sin);
	LUA_ADD_FUNCTION_BY_NAME(L,       "cos", lu5_cos);
	LUA_ADD_FUNCTION_BY_NAME(L,       "tan", lu5_tan);
	LUA_ADD_FUNCTION_BY_NAME(L,       "max", lu5_max);
	LUA_ADD_FUNCTION_BY_NAME(L,       "min", lu5_min);
	LUA_ADD_FUNCTION_BY_NAME(L,       "abs", lu5_abs);
	LUA_ADD_FUNCTION_BY_NAME(L,       "map", lu5_map);
	LUA_ADD_FUNCTION_BY_NAME(L,      "dist", lu5_dist);
	LUA_ADD_FUNCTION_BY_NAME(L, "constrain", lu5_constrain);


	lu5_register_constants(L);
}

void lu5_register_number_array(lua_State *L, const char* array_name, double *list, size_t size)
{
	lua_newtable(L);

	for (int i = 0; i < size; i++) {
		lua_pushnumber(L, i+1);
		lua_pushnumber(L, list[i]);
		lua_settable(L, -3);
	}

	lua_setglobal(L, array_name);  
}

void lu5_register_integer_array(lua_State *L, const char* array_name, int *list, size_t size)
{
	lua_newtable(L);

	for (int i = 0; i < size; i++) {
		lua_pushnumber(L, i+1);
		lua_pushinteger(L, list[i]);
		lua_settable(L, -3);
	}

	lua_setglobal(L, array_name);  
}

void lu5_register_string_array(lua_State *L, const char* array_name, const char **list, size_t size)
{
	lua_newtable(L);

	for (int i = 0; i < size; i++) {
		lua_pushnumber(L, i+1);
		lua_pushstring(L, list[i]);
		lua_settable(L, -3);
	}

	lua_setglobal(L, array_name);  
}
