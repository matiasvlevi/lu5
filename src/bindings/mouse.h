#ifndef _LU5_MOUSE_H_
#define _LU5_MOUSE_H_

/**
 * @brief mouseY
 * @global
 *
 * The y mouse coordinate
 *
 * @example
 * createWindow(400, 400);
 *
 * function draw()
 *   background(51);
 *   
 *   line(0, mouseY, width, mouseY);
 * end
 * @example
 */
#define LU5_MOUSE_Y "mouseY"

/**
 * @brief mouseX
 * @global
 * 
 * The x mouse coordinate
 *
 * @example
 * createWindow(400, 400);
 *
 * function draw()
 *   background(51);
 *   
 *   line(mouseX, 0, mouseX, height);
 * end
 * @example
 */
#define LU5_MOUSE_X "mouseX"

/**
 * @brief pmouseY
 * @global
 *
 * The y mouse coordinate from the previous draw call
 */
#define LU5_PMOUSE_Y "pmouseY"

/**
 * @brief pmouseX
 * @global
 *
 * The x mouse coordinate from the previous draw call
 */
#define LU5_PMOUSE_X "pmouseX"


/**
 * @brief mouseIsPressed
 * @global
 * 
 * Is `true` when the mouse is pressed, is `false` when it's not
 */
#define LU5_MOUSE_IS_PRESSED "mouseIsPressed"

/**
 * @brief mousePressed
 *
 * Called when a mouse button is pressed.
 *
 * @param button The pressed mouse button
 *
 * <br/>
 * In the following example, the circle's size increases when the user clicks the mouse.
 *
 * @example
 * size = 0;
 *
 * function setup()
 *   createWindow(400, 400);
 * end
 *
 * function draw()
 *   background(51);
 *
 *   circle(mouseX, mouseY, size);
 * end
 *
 * -- Increase circle size when mouse pressed
 * function mousePressed()
 *   size = size + 1;
 * end
 * @example
 */
#define LU5_MOUSE_PRESSED "mousePressed"

/**
 * @brief mouseReleased
 *
 * Called when a mouse button is released.
 *
 * @param button The released mouse button
 *
 * <br/>
 * In the following example, the circle's size increases when the user clicks the mouse.
 *
 * @example
 * size = 32;
 *
 * function setup()
 *   createWindow(400, 400);
 * end
 *
 * function draw()
 *   background(51);
 *
 *   circle(mouseX, mouseY, size);
 * end
 *
 * -- Set larger circle size
 * function mousePressed()
 *   size = 64;
 * end
 *
 * -- Reset size
 * function mouseReleased()
 *   size = size + 6;
 * end
 * @example
 */
#define LU5_MOUSE_RELEASED "mouseReleased"

/**
 * @brief mouseWheel
 *
 * Called when a mouse wheel is used
 *
 * @param button The pressed mouse button
 *
 * <br/>
 * In the following example, the circle's size changes when the user scrolls
 *
 * @example
 * size = 0;
 *
 * function setup()
 *   createWindow(400, 400);
 * end
 *
 * function draw()
 *   background(51);
 *
 *   circle(mouseX, mouseY, size);
 * end
 *
 * -- Change circle size when mouse is scrolled
 * function mouseWheel(delta)
 *   size = size + delta;
 * end
 * @example
 */
#define LU5_MOUSE_WHEEL "mouseWheel"

#endif