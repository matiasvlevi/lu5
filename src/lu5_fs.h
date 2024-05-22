#ifndef _LU5_FS_H_
#define _LU5_FS_H_

#include <stddef.h>
#include <stdio.h>

#define LU5_FILE_EXISTS(filename, info) (stat(filename, info) == 0)
#define LU5_FILE_NOT_EXISTS(filename, info) (stat(filename, info) != 0)


/**
 *
 * Get a new allocated string without the file extention
 *
 */ 
char *lu5_name_without_extention(const char *filename);

/**
 * Open a file ptr while handling errors
 */ 
FILE *lu5_open_file(const char *path, const char *mode);

/**
 * Write to a file
 */ 
int lu5_write_file(const char *path, const void *buffer, size_t len);

/**
 * Read a file entirely
 *
 * caller must free the returned buffer.
 */
char* lu5_read_file(const char* path, long *size);


#endif
