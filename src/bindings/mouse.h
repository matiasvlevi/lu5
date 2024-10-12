#ifndef _LU5_MOUSE_H_
#define _LU5_MOUSE_H_

/**
 * @brief mouseY
 * @global
 *
 * The y mouse coordinate.
 *
 * @visual
 *
 * @example
 * createWindow(200, 200);
 * stroke(255);
 *
 * function draw()
 *   background('purple');
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
 * The x mouse coordinate.
 *
 * @visual
 *
 * @example
 * createWindow(200, 200);
 * stroke(255);
 *
 * function draw()
 *   background('purple');
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
 * The y mouse coordinate from the previous draw call.
 */
#define LU5_PMOUSE_Y "pmouseY"

/**
 * @brief pmouseX
 * @global
 *
 * The x mouse coordinate from the previous draw call.
 */
#define LU5_PMOUSE_X "pmouseX"


/**
 * @brief mouseIsPressed
 * @global
 * 
 * Is `true` when the mouse is pressed, is `false` when it's not.
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
 * @visual
 * @example
 * size = 12;
 *
 * function setup()
 *   createWindow(400, 400);
 *   textAlign(CENTER);
 * end
 *
 * function draw()
 *   background('purple');
 *   
 *   text('Click to grow the circle', width/2, 50);
 *   circle(width/2, height/2, size);
 * end
 *
 * -- Increase circle size when mouse pressed
 * function mousePressed()
 *   size = size + 3;
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
 * @visual
 *
 * @example
 * size = 12;
 *
 * function setup()
 *   createWindow(400, 400);
 *   textAlign(CENTER);
 * end
 *
 * function draw()
 *   background('purple');
 *   
 *   text('Click to grow the circle', width/2, 50);
 *   circle(width/2, height/2, size);
 * end
 *
 * -- Increase circle size when mouse released
 * function mouseReleased()
 *   size = size + 3;
 * end
 * @example
 */
#define LU5_MOUSE_RELEASED "mouseReleased"

/**
 * @brief mouseWheel
 *
 * Called when a mouse wheel is used.
 *
 * @param button The pressed mouse button
 *
 * <br/>
 * In the following example, the circle's size changes when the user scrolls.
 *
 * @visual
 *
 * @example
 * size = 32;
 *
 * function setup()
 *   createWindow(400, 400);
 *   textAlign(CENTER);
 * end
 *
 * function draw()
 *   background('purple');
 *   
 *   text('Scroll to change the size', width/2, 50);
 *   circle(width/2, height/2, size);
 * end
 *
 * -- Increase circle size when mouse scrolled
 * function mouseWheel(delta)
 *   size = max(size - delta * 3, 3);
 * end
 * @example
 */
#define LU5_MOUSE_WHEEL "mouseWheel"

#endif