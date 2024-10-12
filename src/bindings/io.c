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
	
	if (argc == 0) {
		putchar('\n');
		return 0;
	}
	
	// Print all arguments
	for (int i = 1; i < argc; i++) {
		lu5_print_any(L, i, 0, ' ');
	}

	lu5_print_any(L, argc, 0, LU5_NEWLINE);

	fflush(stdout);

	return 0;
}

int loadJSON(lua_State *L) {
	return 0;
}

int loadText(lua_State *L) {

	const char* file_path = lu5_assert_string(L, 1, "loadText");

	long file_size = 0;
	
	char* content = lu5_read_file(file_path, &file_size);
	if (content == NULL) {
		lua_pushnil(L);
		return 1;
	}

	lua_pushlstring(L, content, file_size);

	if (content != NULL) 
		free(content);

	return 1;
}

int loadStrings(lua_State *L) {

	const char* file_path = lu5_assert_string(L, 1, "loadStrings");

	FILE* file = lu5_open_file(file_path, "r");
	if (file == NULL) {
		lua_pushnil(L);
		return 1;
	}

    lua_newtable(L);

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int line_number = 1;
    while ((read = getline(&line, &len, file)) != -1) {
        if (line[read - 1] == '\n') {
			// Remove trailing newline character
            line[read - 1] = '\0';
        }
        lua_pushstring(L, line);
        lua_rawseti(L, -2, line_number++);
    }

    if (line) {
        free(line);
    }

    fclose(file);
    return 1;
}