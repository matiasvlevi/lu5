#include <stdlib.h>
#include <stdio.h>

#include "lu5_logger.h"
#include "lu5_cli_options.h"

#include "lu5_state.h"
#include "lu5_fs.h"

#include <sys/stat.h>
#include <errno.h>

#include <string.h>

#define LU5_SKETCH_BOILERPLATE \
		"\n"\
		"function setup()\n"\
		"   createWindow(600, 600);\n"\
		"end\n"\
		"\n"\
		"function draw()\n"\
		"   background(51);\n"\
		"end\n"\

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
	},
	{
		.name = "install",
		.description = "Install a lu5 sketch on the system globally",
		.example = "lu5 --install sketch.lua",
		.handler = lu5_option_install,
		.arg_count = 1
	}
};

int lu5_option_log(int argc, char **argv, int idx, int cli_id, bool* defaultExec, char **filename) 
{

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
	if (argv[arg_1] == end) {
		if (errno) {
			LU5_ERROR("Invalid parameter in %s option, expected number but got %s", argv[idx], argv[arg_1]);
		} else {
			LU5_ERROR("%s\n %s option, expected number but got %s", strerror(errno), argv[idx], argv[arg_1]);
		}
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

	// If file exists
	struct stat file_info;
	if (stat(*filename, &file_info) == 0) {
		
		LU5_WARN(
			"It seems that \x1b[90m%s\x1b[0m already exists", 
			*filename
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

	FILE *file = lu5_open_file(*filename, "wr");
	if (file == NULL) return 1;

	LU5_INFO("Writing %s", *filename);

	// Write to file
	fprintf(file, LU5_SKETCH_BOILERPLATE);

	// Close the file
	fclose(file);

	return 0;
}

int lu5_option_install(int argc, char **argv, int idx, int cli_id, bool* defaultExec, char **filename) 
{
#ifdef _WIN32
	LU5_WARN("Feature not implemented for windows yet. exiting.");
	
	// avoid unused warnings
	(void)lu5_read_file;
	(void)lu5_write_file;

	return 0;
#else
	// option position + nb of args must be smaller than argc
	if (idx+cli_options[cli_id].arg_count >= argc) {
		LU5_ERROR(LU5_FILE_NOT_SPECIFIED);
		return 1;
	}

	int arg_1 = idx+1;

	// first option argument is filename
	*filename = argv[arg_1];

	// If does not file exist
	struct stat file_info;
	if LU5_FILE_NOT_EXISTS(*filename, &file_info) {
		
		LU5_ERROR(
			"Could not find \x1b[90m'%s'\x1b[0m", 
			argv[arg_1]
		);

		if (errno) LU5_ERROR("errno: %i", errno);
		
		return 1;
	}

	char *installed_path, 
		 *first_line_str, 
		 *sketch_source, 
		 *sketch_name = lu5_name_without_extention(*filename);

	int sketch_name_len = strlen(sketch_name);

	// Create a destination path
	installed_path = malloc(sketch_name_len + 10);
	if (!installed_path) {
		LU5_ERROR("Not enough memory to allocate \x1b[90m'%s'\x1b[0m source in heap", *filename);

		free(sketch_name);
		return 1;
	}

	// Format destination path
	sprintf(installed_path, "/usr/bin/%s", sketch_name);

	// Check if file at path exists
	struct stat dest_file_info;
	if (LU5_FILE_EXISTS(installed_path, &dest_file_info)) {

		LU5_ERROR(
			"\x1b[90m'%s'\x1b[0m already exists, cancelling.",
			installed_path
		);

		if (errno) LU5_ERROR("errno: %i", errno);

		free(installed_path);
		return 1;
	}

	LU5_INFO("Installing %s to %s", *filename, installed_path);

	// Read the source file
	long sketch_length;
	sketch_source = lu5_read_file(*filename, &sketch_length);

	// check for hashbang
	const char *hashbang = "#!/usr/bin/lu5";
	const char *end_line = strchr(sketch_source, '\n');
	int first_line_length = (end_line) ? (end_line - sketch_source) : sketch_length;

	// 
	first_line_str = malloc(first_line_length+1);
	if (!first_line_str) {
		LU5_ERROR("Not enough memory to allocate \x1b[90m'%s'\x1b[0m source in heap", *filename);

		free(installed_path);
		free(sketch_source);
		return 1;
	}

	strncpy(first_line_str, sketch_source, first_line_length);
	if (strstr(first_line_str, hashbang) == NULL) {
		LU5_ERROR("lu5 sketch \x1b[90m'%s'\x1b[0m must have a hashbang \x1b[90m'%s'\x1b[0m as the first line of the script.", *filename, hashbang);

		free(installed_path);
		free(sketch_source);
		free(first_line_str);
		return 1;
	}

	// Write to destination file
	if (lu5_write_file(installed_path, sketch_source, sketch_length)) {
		// Error handled in write file
		free(installed_path);
		free(sketch_source);
		free(first_line_str);
		return 1;
	}

	// Set execute permitions for everyone
	int err = chmod(
		installed_path, 
		S_IRUSR | S_IWUSR | S_IXUSR |
        		  S_IRGRP | S_IXGRP |
        		  S_IROTH | S_IXOTH
	);

    if (err) {
		LU5_ERROR("Could not properly install \x1b[90m'%s'\x1b[0m err: %i, errno: %i", *filename, err, errno);
		err = 1;
    }

	// Clear allocated strings
	if (installed_path != NULL) 
		free(installed_path);

	if (sketch_source != NULL) 
		free(sketch_source);
	
	if (first_line_str != NULL) 
		free(first_line_str);

	if (sketch_name != NULL) 
		free(sketch_name);

	return err;
#endif
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
