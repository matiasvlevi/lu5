#ifndef _LU5_FS_H_
#define _LU5_FS_H_

#include <stddef.h>

#define LU5_FILE_EXISTS(filename, info) (stat(filename, info) == 0)
#define LU5_FILE_NOT_EXISTS(filename, info) (stat(filename, info) != 0)

char *lu5_get_file_name(const char *filename);


int lu5_write_file(const char *path, const void *buffer, size_t len);

/**
 * Read a file entirely
 *
 * caller must free the returned buffer.
 */
char* lu5_read_file(const char* path, long *size);


#endif