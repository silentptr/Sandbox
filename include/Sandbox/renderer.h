#ifndef SANDBOX_RENDERER_H_
#define SANDBOX_RENDERER_H_

#include "Sandbox/shader.h"

typedef struct
{
    Shader shader;
    GLuint vao, vbo, ebo;
} Renderer;

bool SB_Renderer_Create(Renderer*);

void SB_Renderer_TestDraw(Renderer*);

#endif