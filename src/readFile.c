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

char* readShaderSourceFromFile(const char* shaderFile) {
    FILE *fp;
    long length;
    char *buffer;

    // Open file and check if it is opened
    fp = fopen(shaderFile, "rb");
    if (fp == NULL) {
        printf("Failed to load %s\n", shaderFile);
        return NULL;
    }

    // Get the length of the file
    fseek(fp, 0L, SEEK_END);
    length = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    // Allocate memory for the entire file
    buffer = malloc(length + 1);
    if (buffer == NULL) {
        printf("Failed to allocate memory for %s\n", shaderFile);
        fclose(fp);
        return NULL;
    }

    // Read the file into the buffer and null-terminate it
    fread(buffer, length, 1, fp);
    buffer[length] = '\0';

    fclose(fp);
    return buffer;
}



