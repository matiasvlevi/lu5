#include <stdlib.h>
#include <stdio.h>

#include "lu5_defs.h"
#include "lu5_logger.h"
#include "lu5_cli_options.h"

#include "lu5_state.h"

#include <sys/stat.h>
#include <errno.h>

lu5_option cli_options[LU5_OPTION_COUNT] = {
	{
		.name = "help",
		.description = "Displays this help meny",
		.example = "",
		.handler = lu5_option_help,
		.arg_count = 0
	},
	{
		.name = "init",
		.description = "Creates a lu5 sketch",
		.example = "lu5 --init sketch.lua",
		.handler = lu5_option_init,
		.arg_count = 1
	},
	{
		.name = "log",
		.description = " Set lu5's log level. Value 0 will disable all logs",
		.example = "lu5 sketch.lua --log 1",
		.handler = lu5_option_log,
		.arg_count = 1
	}
};

int lu5_option_log(int argc, char **argv, int idx, int cli_id, bool* defaultExec, char **filename) {

	// option position + nb of args must be smaller than argc
	if (idx+cli_options[cli_id].arg_count >= argc) {
		LU5_ERROR("%s option expected a log level value from 0 to %i", argv[idx], LU5_WARN_LOG);
		return 1;
	}

	int arg_1 = idx+1;

	// Convert first option argument
	char *end = NULL;
	int log_level = strtol(argv[arg_1], &end, 10);

	/* reset errno to 0 before call */
	errno = 0;

	// Check if error during parsing
	if (
		(argv[arg_1] == end) ||
		(errno == ERANGE && log_level == LONG_MIN) ||
		(errno == ERANGE && log_level == LONG_MAX) ||
		(errno == EINVAL) ||
		(errno != 0 && log_level == 0)
	) {
		LU5_ERROR("Invalid parameter in %s option, expected number but got %s", argv[idx], argv[arg_1]);
	}

	// Check if number parsed correctly
	if (
		(errno == 0 && argv[arg_1] && !*end) ||
		(errno == 0 && argv[arg_1] && *end != 0)
	) {
		// Set the log level
		lu5.log_level = log_level;
	}

	return 0;
}

int lu5_option_init(int argc, char **argv, int idx, int cli_id, bool* defaultExec, char **filename) 
{
	// option position + nb of args must be smaller than argc
	if (idx+cli_options[cli_id].arg_count >= argc) {
		LU5_ERROR(LU5_FILE_NOT_SPECIFIED);
		return 1;
	}

	int arg_1 = idx+1;

	// first option argument is filename
	*filename = argv[arg_1];
	struct stat buffer;

	// If file exists
	if (stat(*filename, &buffer) == 0) {
		
		LU5_WARN(
			"It seems that \x1b[90m%s\x1b[0m already exists", 
			argv[arg_1]
		);

		printf("Do you want to overwrite the sketch? (y/N):");

		char overwrite = getchar();
		if (overwrite == EOF) {
			LU5_ERROR("Failed to read input (will not overwrite \x1b[90m%s\x1b[0m)", *filename);
			return 0;
		}

		// Allow running the file
		*defaultExec = true;

		if (overwrite != 'y') {

			LU5_INFO("Kept the old %s", *filename);

			return 0;
		}
	
	}

	FILE *sketch = fopen(argv[arg_1], "w");

	LU5_INFO("Overwriting %s", *filename);

	// Write to file
	fprintf(sketch, LU5_SKETCH_BOILERPLATE);

	// Close the file
	fclose(sketch);

	return 0;
}

int lu5_option_help(int argc, char **argv, int idx, int cli_id, bool* defaultExec, char **filename) 
{   
	for (int i = 0; i < LU5_OPTION_COUNT; i++) {

		printf(
			"\n\x1b[4;36m--%s\x1b[0m  "
			"%s\n",
			cli_options[i].name, 
			cli_options[i].description
		);

		if (cli_options[i].example[0] != '\0') {
			printf(
				"\t\x1b[90mexample: %s\x1b[0m\n",
				cli_options[i].example
			);

		}

	}

	putc('\n', stdout);

	return 0;
}
