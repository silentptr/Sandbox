#ifndef SANDBOX_SHADER_H_
#define SANDBOX_SHADER_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Sandbox/gl.h"

typedef struct
{
    GLuint program;
} Shader;

// first param is where to store result
// second param is null terminated string for vertex shader
// third param is same thing but fragment shader
bool SB_Shader_Create(Shader*, const char*, const char*);

bool SB_Shader_FromFile(Shader*, const char*, const char*);


#endif