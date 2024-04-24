#ifndef __READ_FILE_H__
#define __READ_FILE_H__

#include <stdio.h>
#include <stdlib.h>

char *readFile(FILE *file);

char* readShaderSourceFromFile(const char* shaderFile);

#endif
