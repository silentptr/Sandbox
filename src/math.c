#include "Sandbox/math.h"

Vector4 SB_Vector4_New(float x, float y, float z, float w)
{
    return (Vector4){x, y, z, w};
}

Matrix4 SB_Matrix4_Identity(void)
{
    Matrix4 mat4;
    memset(&mat4, 0, sizeof(Matrix4));
    mat4.mat[0] = 1.0f;
    mat4.mat[5] = 1.0f;
    mat4.mat[10] = 1.0f;
    mat4.mat[15] = 1.0f;
    return mat4;
}