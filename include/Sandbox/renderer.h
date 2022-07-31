#ifndef SANDBOX_RENDERER_H_
#define SANDBOX_RENDERER_H_

#include "Sandbox/shader.h"
#include "Sandbox/window.h"
#include "Sandbox/texture.h"

typedef struct
{
    Window* windowptr;
    Shader shader;
    GLuint vao, vbo, ebo;
} Renderer;

bool SB_Renderer_Create(Renderer*, Window*);
void SB_Renderer_Draw(Renderer*, Texture2D*, Rectangle*, float, Vector2*);

#endif