#include <stdio.h>
#include <stdlib.h>

#include <lauxlib.h>
#include <lualib.h>

#include "./lu5_state.h"
#include "./lu5_core.h"
#include "./lu5_cli.h"

int main(int argc, char **argv) 
{
	char *filename;
	// return if option ran
	if (!handle_args(argc, argv, &filename)) {
		return 0;
	}

	if (!glfwInit()) {
		luaL_error(lu5.L, "Failed to initialize GLFW\n");
		return 1;
	}

	do {
		lu5_run_sketch(&lu5, filename);
	} while(lu5.env.restart);

	LU5_INFO(LU5_EXIT_APP);
	glfwTerminate();

	return 0;
}
