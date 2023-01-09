#version 460 core

// input variables
layout (location = 0) in vec4 vertexPosition;
layout (location = 1) in float vertexSize;
layout (location = 3) in vec4 vertexColor;

// output variables
out vec4 color;
out vec4 pos;
out float vSize;

// uniform variables
uniform mat4 model;
uniform mat4 view;

void main() {
    pos = vertexPosition;
    vSize = vertexSize / 40.0f;

    // set the color of the particle
    color = vertexColor;

    // transform the vertex position using the model-view and projection matrices
    gl_Position = view * model * vertexPosition;
}