#ifndef _LU5_CLASSES_H_
#define _LU5_CLASSES_H_
#include <lua.h>
/**
 * Create a class. 
 * if a class implements a `print` method, it can be used in the <a href="./io.html#print">`print`</a> function.
 * 
 * @param name The class name
 *
 * @example
 * local Player = class('Player');
 *
 * function Player:init(x, y)
 *   self.x = x;
 *   self.y = y;
 *   return self;
 * end
 *
 * function Player:draw()
 *   circle(self.x, self.y, 16);
 * end
 *
 *
 * -- Create 2 players and draw them
 * local p1 = Player:new(100, 200);
 * local p2 = Player:new(300, 200);
 *
 * function setup()
 *   createWindow(400, 400);
 * end
 * 
 * function draw()
 *   background('purple');
 *
 *   p1:draw();
 *   p2:draw();
 * end
 * @example
 */
int lu5_class(lua_State *L);

#endif