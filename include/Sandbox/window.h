#ifndef SANDBOX_WINDOW_H_
#define SANDBOX_WINDOW_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Sandbox/gl.h"

typedef struct
{
    uint16_t width;
    uint16_t height;
    GLFWwindow* handle;
} Window;

Window* SB_CreateWindow(uint16_t, uint16_t);
void SB_DestroyWindow(Window*);
void SB_UpdateWindowTitle(Window*, uint32_t, uint32_t);

#endif