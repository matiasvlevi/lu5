#include "shaders.h"

#include <stdio.h>
#include <stdlib.h>
#include "readFile.h"

#include <GLFW/glfw3.h>

void compile_shaders() 
{
    char* rline_vertexShaderSource = readShaderSourceFromFile("./shaders/rline_vertex.glsl");
    char* rline_fragmentShaderSource = readShaderSourceFromFile("./shaders/rline_fragment.glsl");

    if(rline_vertexShaderSource == NULL || rline_fragmentShaderSource == NULL) {
        // Handle error; for example, exit the program
        exit(EXIT_FAILURE);
    }

    GLuint rline_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(rline_vertexShader, 1, (const GLchar **)&rline_vertexShaderSource, NULL);
    glCompileShader(rline_vertexShader);
    // Check for shader compile errors...

    GLuint rline_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(rline_fragmentShader, 1, (const GLchar **)&rline_fragmentShaderSource, NULL);
    glCompileShader(rline_fragmentShader);
    // Check for shader compile errors...

    // Link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, rline_vertexShader);
    glAttachShader(shaderProgram, rline_fragmentShader);
    glLinkProgram(shaderProgram);
    // Check for linking errors...

    // Deallocation
    free(rline_vertexShaderSource);
    free(rline_fragmentShaderSource);
    glDeleteShader(rline_vertexShader);
    glDeleteShader(rline_fragmentShader);
}
