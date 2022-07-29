#ifndef SANDBOX_WINDOW_H_
#define SANDBOX_WINDOW_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Sandbox/OGL.h"

typedef struct
{
    uint16_t width;
    uint16_t height;
    GLFWwindow* handle;
} Window;

Window* SBCreateWindow(uint16_t, uint16_t);
void SBDestroyWindow(Window*);
void SBUpdateWindowTitle(Window*, uint32_t, uint32_t);

#endif