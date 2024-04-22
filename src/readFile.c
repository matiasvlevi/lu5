#include "readFile.h"

char *readFile(FILE *file) {
    char *code;
    size_t n = 0;
    int c;

    if (file == NULL) return NULL;

    // Get Size
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Alloc
    code = (char*)malloc(f_size);

    // Fill up the buffer
    while ((c = fgetc(file)) != EOF) {
        code[n++] = (char)c;
    }

    // Add termination
    code[n] = '\0';        

    // return ptr
    return code;
}


