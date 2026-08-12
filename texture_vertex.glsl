#version 300 es

layout(location=0) in vec3 position;
layout(location=1) in vec2 texCoord;

uniform mat4 MVP;

out vec2 uv;

void main()
{
    gl_Position = MVP * vec4(position,1.0);

    uv = texCoord;
}


