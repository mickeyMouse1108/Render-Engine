#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;

out vec4 vColor;

void main() {
    vColor = color;
    gl_Position = position;
}