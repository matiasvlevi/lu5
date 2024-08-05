#include "io.h"

#include <stdlib.h>
#include <string.h>

#include "../lu5_types.h"
#include "../lu5_print.h"
#include "../lu5_logger.h"
#include "../lu5_fs.h"

int print(lua_State *L)
{
	int argc = lua_gettop(L);
	
	// Print all arguments
	for (int i = 1; i < argc; i++) {
		lu5_print_any(L, i, 0, ' ');
	}
	lu5_print_any(L, argc, 0, '\n');

	return 0;
}

int loadJSON(lua_State *L) {
	return 0;
}

int loadText(lua_State *L) {

	const char* file_path = lu5_assert_string(L, 1, "loadText");

	long file_size = 0;
	char* content = lu5_read_file(file_path, &file_size);

	lua_pushlstring(L, content, file_size);

	if (content != NULL) 
		free(content);

	return 1;
}

int loadStrings(lua_State *L) {

	const char* file_path = lu5_assert_string(L, 1, "loadStrings");

	long file_size = 0;
	char* content = lu5_read_file(file_path, &file_size);

	char **lines = NULL;

	char *line = strtok(content, "\n");

	int line_count = 0;
	while (line)
	{
		// Reallocate to add a new line
		lines = realloc(lines, sizeof(char*) * line_count);
		if (lines == NULL) {
			LU5_ERROR("Not enough space to allocate file") 
			return 0;
		}

		// Allocate new line and copy line
		lines[line_count] = malloc(sizeof(char) * strlen(line));
		strcpy(lines[line_count], line);

		// get next line		
		line = strtok(NULL, "\n");
		
		// count spaces
		line_count++;
	}

	// Create table for file lines
	lua_createtable(L, line_count, 0);

	for (int i = 0; i < line_count; i++) {
		// Push new line at corresponding index 
		lua_pushnumber(L, i + 1);
		lua_pushstring(L, lines[i]);
		lua_settable(L, -3);
	}

	if (content != NULL) 
		free(content);

	for (int i = 0; i < line_count; i++)
		free(lines[i]);
	free(lines);

	return 1;
}