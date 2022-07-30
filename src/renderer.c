#include "Sandbox/renderer.h"

bool SB_Renderer_Create(Renderer* renderer, Window* window)
{
    if (!SB_Shader_FromFile(&renderer->shader, "res/shaders/main_vs.glsl", "res/shaders/main_fs.glsl"))
    {
        return false;
    }

    renderer->windowptr = window;
    glGenVertexArrays(1, &renderer->vao);
    glGenBuffers(1, &renderer->vbo);
    glGenBuffers(1, &renderer->ebo);

    glBindVertexArray(renderer->vao);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->ebo);

    glBufferData(GL_ARRAY_BUFFER, 32, NULL, GL_DYNAMIC_DRAW);
    GLuint indices[6];
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 0;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8, (void*)0);
    glEnableVertexAttribArray(0);
    return true;
}

void SB_Renderer_TestDraw(Renderer* renderer)
{
    glUseProgram(renderer->shader.program);
    glBindVertexArray(renderer->vao);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->ebo);
    float vertices[] =
    {
        -.5f, .5f,
        .5f, .5f,
        .5f, -.5f,
        -.5f, -.5f
    };
    glBufferSubData(GL_ARRAY_BUFFER, 0, 32, &vertices[0]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}