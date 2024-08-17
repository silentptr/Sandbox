#include "Sandbox/shader.h"

bool SB_Shader_Create(Shader* shader, const char* vss, const char* fss)
{
    int success;
    char infoLog[1024];

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vss, 0);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vs, 1024, NULL, &infoLog[0]);
        glDeleteShader(vs);
        printf("Vertex shader compile error:\n%s\n", &infoLog[0]);
        return false;
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fss, 0);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vs, 1024, NULL, &infoLog[0]);
        glDeleteShader(vs);
        glDeleteShader(fs);
        printf("Fragment shader compile error:\n%s\n", &infoLog[0]);
        return false;
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(program, 1024, NULL, &infoLog[0]);
        glDeleteProgram(program);
        printf("Shader program linking error:\n%s\n", &infoLog[0]);
        return false;
    }

    shader->program = program;
    return true;
}

bool SB_Shader_FromFile(Shader* shader, const char* vssfile, const char* fssfile)
{
    char vss[1024];
    char fss[1024];
    FILE* fp = fopen(vssfile, "r");

    if (!fp)
    {
        printf("Couldn't open \"%s\".\n", vssfile);
        return false;
    }

    memset(&vss[0], 0, 1024);

    if (fread(&vss[0], 1, 1024, fp) < 1)
    {
        fclose(fp);
        printf("Couldn't read \"%s\".\n", vssfile);
        return false;
    }

    fclose(fp);
    fp = fopen(fssfile, "r");

    if (!fp)
    {
        printf("Couldn't open \"%s\".\n", fssfile);
        return false;
    }

    memset(&fss[0], 0, 1024);

    if (fread(&fss[0], 1, 1024, fp) < 1)
    {
        fclose(fp);
        printf("Couldn't read \"%s\".\n", vssfile);
        return false;
    }

    fclose(fp);
    return SB_Shader_Create(shader, &vss[0], &fss[0]);
}

bool SB_Shader_SetUniformMatrix4(Shader* shader, const char* uniform, Matrix4* mat4)
{
    GLint location = glGetUniformLocation(shader->program, uniform);

    if (location == -1) { return false; }

    float data[16];
    SB_Matrix4_GetGLArray(mat4, &data[0]);
    glUniformMatrix4fv(location, 1, GL_FALSE, &data[0]);
    return true;
}