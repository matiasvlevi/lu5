#ifndef __LU5_SHADERS_H__
#define __LU5_SHADERS_H__


#include <GL/glew.h>
#include <GL/gl.h>

typedef struct {
   struct {
        struct {
            char *vertex;
            char *fragment;
        } rline;
   } source; 
   struct {
        struct {
            GLuint vertex;
            GLuint fragment;
        } rline;
   } shader;
} Shaders;

#endif
