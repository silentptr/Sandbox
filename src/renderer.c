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

    float vertices[] =
    {
        0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
    GLuint indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 16, (void*)0);
    glEnableVertexAttribArray(0);
    return true;
}

void SB_Renderer_Draw(Renderer* renderer, Texture2D* texture, Rectangle* rect, float angle)
{
    glUseProgram(renderer->shader.program);
    glBindVertexArray(renderer->vao);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->ebo);

    Matrix4 projection;
    SB_Matrix4_SetOrtho(&projection, 0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);

    Matrix4 transform;
    SB_Matrix4_SetIdentity(&transform);

    Matrix4 position, scale, rotation, rotationOrigin, rotationOriginNeg;
    SB_Matrix4_SetTranslation(&position, rect->x, rect->y, 0.0f);
    SB_Matrix4_SetScale(&scale, rect->width, rect->height, 0.0f);
    SB_Matrix4_SetRotationZ(&rotation, angle);
    SB_Matrix4_SetTranslation(&rotationOrigin, 0.5f * rect->width, 0.5f * rect->height, 0.0f);
    SB_Matrix4_SetTranslation(&rotationOriginNeg, -0.5f * rect->width, -0.5f * rect->height, 0.0f);

    SB_Matrix4_Multiply(&transform, &position, &transform);
    SB_Matrix4_Multiply(&transform, &rotationOrigin, &transform);
    SB_Matrix4_Multiply(&transform, &rotation, &transform);
    SB_Matrix4_Multiply(&transform, &rotationOriginNeg, &transform);
    SB_Matrix4_Multiply(&transform, &scale, &transform);

    SB_Shader_SetUniformMatrix4(&renderer->shader, "projection", &projection);
    SB_Shader_SetUniformMatrix4(&renderer->shader, "transform", &transform);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->handle);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}