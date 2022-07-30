#ifndef SANDBOX_SHADER_H_
#define SANDBOX_SHADER_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Sandbox/gl.h"
#include "Sandbox/math.h"

typedef struct
{
    GLuint program;
} Shader;

bool SB_Shader_Create(Shader*, const char*, const char*);
bool SB_Shader_FromFile(Shader*, const char*, const char*);
bool SB_Shader_SetUniformMatrix4(Shader*, const char*, Matrix4*);

#endif