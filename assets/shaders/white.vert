#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec3 aNormal;

//out vec2 uv;
//out vec3 worldPosition;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
    vec4 transformedPosition = modelMatrix * vec4(aPos, 1.f);
    gl_Position = projectionMatrix * viewMatrix * transformedPosition;
//    uv = aUV;
//    worldPosition = transformedPosition.xyz;
}
