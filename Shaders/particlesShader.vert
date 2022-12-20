#version 460 core

// input variables
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in float vertexSize;
layout (location = 2) in float vertexRadius;
layout (location = 3) in vec3 vertexColor;
layout (location = 4) in vec3 vertexVelocity;
layout (location = 5) in float vertexMass;

// output variables
out vec3 color;
out vec3 pos;
out float vSize;

// uniform variables
uniform mat4 model;
uniform mat4 view;

void main() {
    pos = vertexPosition;
    vSize = vertexSize / 10.0f;

    // set the color of the particle
    color = vertexColor;

    // set the size of the particle
    // gl_PointSize = vertexSize;

    // transform the vertex position using the model-view and projection matrices
    gl_Position = view * model * vec4(vertexPosition, 1.0);
}