#version 450 core

layout (location = 0) in vec4 vertData;

out vec2 texCoords;

uniform mat4 projection;
uniform mat4 transform;

void main()
{
    texCoords = vec2(vertData.z, vertData.w);
    gl_Position = projection * transform * vec4(vertData.x, vertData.y, 0.0, 1.0);
}