#include "Sandbox/math.h"
#include <string.h>

void SB_Rectangle_Set(Rectangle* rect, float x, float y, float width, float height)
{
    rect->x = x;
    rect->y = y;
    rect->width = width;
    rect->height = height;
}

void SB_Matrix4_Multiply(Matrix4* leftMat4, Matrix4* rightMat4, Matrix4* result)
{
    float left[16];
    memcpy(&left, &leftMat4->data[0], sizeof(Matrix4));
    float right[16];
    memcpy(&right, &rightMat4->data[0], sizeof(Matrix4));
    result->data[0] = left[0] * right[0] + left[1] * right[4] + left[2] * right[8] + left[3] * right[12];
    result->data[1] = left[0] * right[1] + left[1] * right[5] + left[2] * right[9] + left[3] * right[13];
    result->data[2] = left[0] * right[2] + left[1] * right[6] + left[2] * right[10] + left[3] * right[14];
    result->data[3] = left[0] * right[3] + left[1] * right[7] + left[2] * right[11] + left[3] * right[15];
    result->data[4] = left[4] * right[0] + left[5] * right[4] + left[6] * right[8] + left[7] * right[12];
    result->data[5] = left[4] * right[1] + left[5] * right[5] + left[6] * right[9] + left[7] * right[13];
    result->data[6] = left[4] * right[2] + left[5] * right[6] + left[6] * right[10] + left[7] * right[14];
    result->data[7] = left[4] * right[3] + left[5] * right[7] + left[6] * right[11] + left[7] * right[15];
    result->data[8] = left[8] * right[0] + left[9] * right[4] + left[10] * right[8] + left[11] * right[12];
    result->data[9] = left[8] * right[1] + left[9] * right[5] + left[10] * right[9] + left[11] * right[13];
    result->data[10] = left[8] * right[2] + left[9] * right[6] + left[10] * right[10] + left[11] * right[14];
    result->data[11] = left[8] * right[3] + left[9] * right[7] + left[10] * right[11] + left[11] * right[15];
    result->data[12] = left[12] * right[0] + left[13] * right[4] + left[14] * right[8] + left[15] * right[12];
    result->data[13] = left[12] * right[1] + left[13] * right[5] + left[14] * right[9] + left[15] * right[13];
    result->data[14] = left[12] * right[2] + left[13] * right[6] + left[14] * right[10] + left[15] * right[14];
    result->data[15] = left[12] * right[3] + left[13] * right[7] + left[14] * right[11] + left[15] * right[15];
}

void SB_Matrix4_SetIdentity(Matrix4* mat4)
{
    memset(mat4, 0, sizeof(Matrix4));
    mat4->data[0] = 1.0f;
    mat4->data[5] = 1.0f;
    mat4->data[10] = 1.0f;
    mat4->data[15] = 1.0f;
}

void SB_Matrix4_SetTranslation(Matrix4* mat4, float x, float y, float z)
{
    SB_Matrix4_SetIdentity(mat4);
    mat4->data[3] = x;
    mat4->data[7] = y;
    mat4->data[11] = z;
}

void SB_Matrix4_SetScale(Matrix4* mat4, float x, float y, float z)
{
    memset(mat4, 0, sizeof(Matrix4));
    mat4->data[0] = x;
    mat4->data[5] = y;
    mat4->data[10] = z;
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