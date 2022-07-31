#version 450 core

layout (location = 0) in vec2 vert;

uniform mat4 projection;
uniform mat4 transform;

void main()
{
    gl_Position = projection * transform * vec4(vert.x, vert.y, 0.0, 1.0);
}