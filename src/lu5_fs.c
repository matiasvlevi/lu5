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

char *lu5_get_file_name(const char *filename) {
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
        return strdup(filename);
    }

    strncpy(name_without_extention, filename, length);
    name_without_extention[length] = '\0';
    
	return name_without_extention;
}

int lu5_write_file(const char *path, const void *buffer, size_t len) {
    // Open the file in binary write mode
    FILE *file = fopen(path, "wb");
    if (file == NULL) {
		switch(errno) {
			case EACCES: {
        		LU5_ERROR("Permission denied when writing \x1b[90m'%s'\x1b[0m", path);
				break;
			}
			default: {
        		LU5_ERROR("Something went wrong when writing \x1b[90m'%s'\x1b[0m, errno: %i", path, errno);
				break;
			}
		}
        return 1;
    }

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

/**
 * Read a file entirely
 *
 * caller must free the returned buffer.
 */
char *lu5_read_file(const char* path, long *size) {
    FILE *fp;
    long length;
    char *buffer;

    // Open the file
    fp = fopen(path, "rb");
    if (fp == NULL) {
		switch(errno) {
			case EACCES: {
        		LU5_ERROR("No permission to read \x1b[90m'%s'\x1b[0m", path);
				break;
			}
			default: {
        		LU5_ERROR("Could not open file: %s\n", path);
				break;
			}
		}
        return NULL;
    }

    // Get the length of the file
    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // Read the file contents
    buffer = (char*)malloc((length + 1) * sizeof(char));
    if (buffer) {
        fread(buffer, sizeof(char), length, fp);
        buffer[length] = '\0'; // Null-terminate the string
    }
    fclose(fp);

	*size = length;

    return buffer;
}
