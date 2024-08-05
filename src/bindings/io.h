#ifndef __LU5_IO_BINDINGS__
#define __LU5_IO_BINDINGS__

#include <lua.h>

/**
 * Printing utility, can take any lua type (except objects).
 *
 * @param value The value to print to stdout
 */ 
int print(lua_State *L);

int loadJSON(lua_State *L);

/**
 * Read a file as a string
 *
 * @param file_path The path of the file
 *
 * @example
 * file = loadText("./your-file.txt");
 * print(file)
 * @example
 */
int loadText(lua_State *L);

/**
 * Read a file as an array of strings split by line
 *
 * @param file_path The path of the file
 *
 * @example
 * file = loadStrings("./your-file.txt");
 * print(file)
 * @example
 */
int loadStrings(lua_State *L);


#endif
