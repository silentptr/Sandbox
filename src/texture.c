#include "Sandbox/texture.h"
#include "Sandbox/stb_image.h"

Texture2D* SB_Texture2D_FromFile(const char* path)
{
    uint32_t width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* data = stbi_load(path, &width, &height, &channels, 4);

    if (!data)
    {
        printf("Couldn't load image \"%s\".\n", path);
        return NULL;
    }

    GLuint handle;
    glGenTextures(1, &handle);
    glBindTexture(GL_TEXTURE_2D, handle);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    Texture2D* result = malloc(sizeof(Texture2D));
    result->width = width;
    result->height = height;
    result->handle = handle;
    return result;
}

void SB_Texture2D_Destroy(Texture2D* texture)
{
    glDeleteTextures(1, &texture->handle);
    free(texture);
}