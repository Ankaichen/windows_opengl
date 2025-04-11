#version 330 core

out vec4 FragColor;

in vec2 uv;

uniform sampler2D sampler;

void main() {
    vec4 samplerColor = texture(sampler, uv);
    FragColor = samplerColor;
}
