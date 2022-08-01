#include <stdio.h>
#include "Sandbox/window.h"
#include "Sandbox/renderer.h"

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

typedef struct
{
    Rectangle rect;
    float rotation;
} ObjectState;

typedef struct
{
    Texture2D* texture;
    ObjectState oldState, state;
} Blueberry;

void LerpObjectState(ObjectState* a, ObjectState* b, ObjectState* result, float t)
{
    result->rect.x = SB_Lerp(a->rect.x, b->rect.x, t);
    result->rect.y = SB_Lerp(a->rect.y, b->rect.y, t);
    result->rotation = SB_Lerp(a->rotation, b->rotation, t);
}

void init(void);
void update(double);
void draw(double);

Window* window;
Renderer* renderer;
Blueberry blueberry;

int main(void)
{
    if (!glfwInit())
    {
        printerr();
        return 1;
    }

    window = SB_CreateWindow(1280, 720);

    if (window == NULL)
    {
        printerr();
        glfwTerminate();
        return 1;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printerr();
        SB_DestroyWindow(window);
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
    init();
    fflush(stdout);

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
            SB_UpdateWindowTitle(window, updates, draws);
            updates = 0;
            draws = 0;
        }
    }

    SB_Renderer_Destroy(renderer);
    SB_Texture2D_Destroy(blueberry.texture);
    SB_DestroyWindow(window);
    glfwTerminate();
    return 0;
}

void init(void)
{
    renderer = SB_Renderer_New(window);
    blueberry.texture = SB_Texture2D_FromFile("res/images/test.jpg");
    blueberry.state.rotation = 0.0f;
    SB_Rectangle_Set(&blueberry.state.rect, 0.0f, 0.0f, 410.0f, 321.0f);
}

void update(double delta)
{
    memcpy(&blueberry.oldState, &blueberry.state, sizeof(ObjectState));
    
    if (glfwGetKey(window->handle, GLFW_KEY_A))
    {
        blueberry.state.rect.x -= 10.0f;
    }

    if (glfwGetKey(window->handle, GLFW_KEY_D))
    {
        blueberry.state.rect.x += 10.0f;
    }

    if (glfwGetKey(window->handle, GLFW_KEY_W))
    {
        blueberry.state.rect.y -= 10.0f;
    }

    if (glfwGetKey(window->handle, GLFW_KEY_S))
    {
        blueberry.state.rect.y += 10.0f;
    }

    if (glfwGetKey(window->handle, GLFW_KEY_MINUS))
    {
        blueberry.state.rotation -= SB_DegreesToRadians(delta * 50.0f);
    }

    if (glfwGetKey(window->handle, GLFW_KEY_EQUAL))
    {
        blueberry.state.rotation += SB_DegreesToRadians(delta * 50.0f);
    }

    if (glfwGetKey(window->handle, GLFW_KEY_R))
    {
        blueberry.state.rotation = 0.0f;
    }
}

void draw(double alpha)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ObjectState state;
    memcpy(&state, &blueberry.state, sizeof(ObjectState));
    LerpObjectState(&blueberry.state, &blueberry.oldState, &state, alpha);
    SB_Renderer_Draw(renderer, blueberry.texture, &state.rect, state.rotation, NULL);
}