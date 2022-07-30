#ifndef SANDBOX_MATH_H_
#define SANDBOX_MATH_H_

// ====================================================================================
// matrices are stored row major
// but need to be transformed to column major when sent to OpenGL
// 00 01 02 03
// 04 05 06 07
// 08 09 10 11
// 12 13 14 15
// ====================================================================================

typedef struct
{
    float data[2];
} Vector2;

typedef struct
{
    float data[3];
} Vector3;

typedef struct
{
    float data[4];
} Vector4;

typedef struct
{
    float data[16];
} Matrix4;

// ===== Matrix4 =====

void SB_Matrix4_SetIdentity(Matrix4*);
void SB_Matrix4_SetOrtho(Matrix4*, float, float, float, float, float, float);
void SB_Matrix4_GetGLArray(Matrix4*, float*);

#endif