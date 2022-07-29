#ifndef SANDBOX_MATH_H_
#define SANDBOX_MATH_H_

#include <string.h>

// matrices are stored row major
// but need to be transformed to column major when sent to OpenGL

typedef struct
{
    float components[2];
} Vector2;

typedef struct
{
    float components[3];
} Vector3;

typedef struct
{
    float components[4];
} Vector4;

typedef struct
{
    float mat[16];
} Matrix4;

Vector4 SB_Vector4_New(float, float, float, float);

Matrix4 SB_Matrix4_Identity(void);

#endif