#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

out vec2 uv;

uniform mat4 transform;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
    vec4 position = vec4(aPos, 1.f);
    gl_Position = projectionMatrix * viewMatrix * transform * position;
    uv = aUV;
}
