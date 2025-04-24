#version 330 core

out vec4 FragColor;

uniform float near;
uniform float far;

void main() {
    float zNdc = gl_FragCoord.z * 2 - 1;
    float linearDepth = 2 * near / (far + near - zNdc * (far - near));
    vec3 finalColor = vec3(linearDepth, linearDepth, linearDepth);
    FragColor = vec4(finalColor, 1.f);
}
