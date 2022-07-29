#include <stdio.h>
#include "Sandbox/window.h"

void printerr(void)
{
    int glfwErrorCode;
    const char* glfwErrorDesc;

    glfwErrorCode = glfwGetError(&glfwErrorDesc);

    if (glfwErrorCode != GLFW_NO_ERROR)
    {
        printf("GLFW [%i]: %s\n", glfwErrorCode, glfwErrorDesc);
    }
}

void update(double);
void draw(double);

int main(void)
{
    if (!glfwInit())
    {
        printerr();
        return 1;
    }

    Window* window = SBCreateWindow(1280, 720);

    if (window == NULL)
    {
        printerr();
        glfwTerminate();
        return 1;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        SBDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    glfwSwapInterval(1);
    glViewport(0, 0, window->width, window->height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    double dt = 1.0 / 60.0;
    double currentTime = glfwGetTime();
    double accumulator = 0.0;
    double newTime;
    double frameTime;
    double now;
    double lastDraw = 0.0;
    double refreshRate = 1.0 / (double)glfwGetVideoMode(glfwGetPrimaryMonitor())->refreshRate;
    uint32_t updates = 0, draws = 0;
    double lastStatCount = 0.0;

    while (!glfwWindowShouldClose(window->handle))
    {
        newTime = glfwGetTime();
        frameTime = newTime - currentTime;
        if (frameTime > 0.25) { frameTime = 0.25; }
        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= dt)
        {
            glfwPollEvents();
            update(dt);
            ++updates;
            accumulator -= dt;
        }

        now = glfwGetTime();

        if (now - lastDraw >= refreshRate)
        {
            lastDraw = now;
            draw(accumulator / dt);
            glfwSwapBuffers(window->handle);
            ++draws;
        }

        now = glfwGetTime();

        if (now - lastStatCount >= 1.0)
        {
            lastStatCount = now;
            SBUpdateWindowTitle(window, updates, draws);
            updates = 0;
            draws = 0;
        }
    }

    SBDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void update(double delta)
{

}

void draw(double alpha)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}