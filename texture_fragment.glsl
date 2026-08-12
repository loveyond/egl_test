#version 300 es


precision mediump float;

uniform sampler2D texture0;

in vec2 uv;

out vec4 fragColor;


void main()
{
    fragColor = texture(texture0,uv);
}

