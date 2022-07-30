#include "Sandbox/math.h"
#include <string.h>

void SB_Matrix4_SetIdentity(Matrix4* mat4)
{
    memset(mat4, 0, sizeof(Matrix4));
    mat4->data[0] = 1.0f;
    mat4->data[5] = 1.0f;
    mat4->data[10] = 1.0f;
    mat4->data[15] = 1.0f;
}

void SB_Matrix4_SetOrtho(Matrix4* mat4, float left, float right, float top, float bottom, float near, float far)
{
    memset(mat4, 0, sizeof(Matrix4));
    mat4->data[0] = 2.0f / (right - left);
    mat4->data[3] = -((right + left) / (right - left));
    mat4->data[5] = 2.0f / (top - bottom);
    mat4->data[7] = -((top + bottom) / (top - bottom));
    mat4->data[10] = -2.0f / (far - near);
    mat4->data[11] = -((far + near) / (far - near));
    mat4->data[15] = 1.0f;
}

void SB_Matrix4_GetGLArray(Matrix4* mat4, float* result)
{
    result[0] = mat4->data[0];
    result[1] = mat4->data[4];
    result[2] = mat4->data[8];
    result[3] = mat4->data[12];
    result[4] = mat4->data[1];
    result[5] = mat4->data[5];
    result[6] = mat4->data[9];
    result[7] = mat4->data[13];
    result[8] = mat4->data[2];
    result[9] = mat4->data[6];
    result[10] = mat4->data[10];
    result[11] = mat4->data[14];
    result[12] = mat4->data[3];
    result[13] = mat4->data[7];
    result[14] = mat4->data[11];
    result[15] = mat4->data[15];
}