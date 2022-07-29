#include "Sandbox/window.h"

Window* SB_CreateWindow(uint16_t w, uint16_t h)
{
    Window* win = (Window*)malloc(sizeof(Window));

    if (win == NULL)
    {
        return NULL;
    }

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    win->handle = glfwCreateWindow(w, h, "Sandbox (OpenGL 4.5)", NULL, NULL);

    if (win->handle == NULL)
    {
        free(win);
        return NULL;
    }

    win->width = w;
    win->height = h;
    glfwMakeContextCurrent(win->handle);
    return win;
}

void SB_DestroyWindow(Window* win)
{
    glfwDestroyWindow(win->handle);
    free(win);
}

void SB_UpdateWindowTitle(Window* window, uint32_t ups, uint32_t fps)
{
    char title[100];
    memset(&title[0], 0, 100);
    sprintf(&title[0], "Sandbox [UPS: %i, FPS: %i] (OpenGL 4.5 core)", ups, fps);
    glfwSetWindowTitle(window->handle, &title[0]);
}