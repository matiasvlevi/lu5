#ifndef __LU5_IO_BINDINGS__
#define __LU5_IO_BINDINGS__

#include <lua.h>

/**
 * Printing utility, can take any lua type.
 *
 * @param value The value to print to stdout
 *
 * @example @live
 * print(42);
 *
 * print(1, 2, 3);
 * 
 * print('Hello world');
 *
 * print({ 3, 8, 1 });
 * @example
 */ 
int print(lua_State *L);

int loadJSON(lua_State *L);

/**
 * Read a file as a string.
 *
 * @param file_path The path of the file
 *
 * @example @live
 * file = loadText("./your-file.txt");
 * print(file);
 * @example
 */
int loadText(lua_State *L);

/**
 * Read a file as an array of strings split by line.
 *
 * @param file_path The path of the file
 *
 * @example @live
 * file = loadStrings("./your-file.txt");
 * print(file);
 * @example
 */
int loadStrings(lua_State *L);


#endif
