#include "lu5_fs.h"

#include <stdio.h>
#include <stdlib.h>

#include "lu5_logger.h"

#include <sys/stat.h>
#include <errno.h>

#include <string.h>

// Forward declare strdup 
// is required for some systems
char* strdup(const char*);

char *lu5_name_without_extention(const char *filename) 
{
    // Find the last dot in the filename
    char *dot = strrchr(filename, '.');
    if (!dot || dot == filename) {
        return strdup(filename);
	}

	// Get the position of the dot
    size_t length = dot - filename;
    
	// Allocate memory for the new string
    char *name_without_extention = (char *)malloc(length + 1);
    if (!name_without_extention) {
        LU5_ERROR("No memory left on the device");
        return NULL;
    }

    strncpy(name_without_extention, filename, length);
    name_without_extention[length] = '\0';
    
	return name_without_extention;
}


FILE *lu5_open_file(const char *path, const char *mode) 
{
    errno = 0;
	FILE *file = fopen(path, mode);
    if (file == NULL) {
		if (errno) {
			LU5_ERROR("%s", strerror(errno));
		} else {
        	LU5_ERROR("Something went wrong when opening file \x1b[90m'%s'\x1b[0m", path);
		}
    }
	return file;
}

int lu5_write_file(const char *path, const void *buffer, size_t len) 
{
	FILE *file = lu5_open_file(path, "wb");
	if (file == NULL) return 1;

    // Write the buffer to the file
    size_t written = fwrite(buffer, 1, len, file);
    if (written != len) {
        LU5_ERROR("Error writing to \x1b[90m'%s'\x1b[0m", path);
        return 1;
    }

    // Close the file
    fclose(file);
    return 0;
}

char *lu5_read_file(const char* path, long *size) {
    
	FILE *file = lu5_open_file(path, "rb");
	if (file == NULL) return NULL;

    // Get the length of the file
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Read the file contents
    char *buffer = (char*)malloc((length + 1) * sizeof(char));
    if (buffer == NULL) {
		LU5_ERROR("Could not allocate memory for file");

		fclose(file);
		return NULL;
	}

	// Read file
	fread(buffer, sizeof(char), length, file);

	// Add null-termination
	buffer[length] = '\0';

    fclose(file);

	// Set length return
	*size = length;

    return buffer;
}
