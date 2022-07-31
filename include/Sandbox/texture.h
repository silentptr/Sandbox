#ifndef SANDBOX_TEXTURE_H_
#define SANDBOX_TEXTURE_H_

#include <stdint.h>
#include <stdbool.h>
#include "Sandbox/gl.h"

typedef struct
{
    GLuint handle;
    uint32_t width;
    uint32_t height;
} Texture2D;

bool SB_Texture2D_FromFile(Texture2D*, const char*);

#endif