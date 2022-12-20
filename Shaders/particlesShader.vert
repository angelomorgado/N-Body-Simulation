#version 460 core

// input variables
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec4 texCoords;
layout (location = 2) in vec3 vertexColor;
layout (location = 3) in float vertexSize;
layout (location = 4) in float vertexMass;
layout (location = 5) in vec3 vertexVelocity;
layout (location = 6) in float vertexRadius;

// output variables
out vec3 color;
out vec3 pos;
out float vSize;

// uniform variables
uniform mat4 model;
uniform mat4 view;

void main() {
    pos = vertexPosition;
    vSize = vertexRadius;

    // set the color of the particle
    color = vertexColor;

    // set the size of the particle
    gl_PointSize = vertexSize;

    // transform the vertex position using the model-view and projection matrices
    gl_Position = view * model * vec4(vertexPosition, 1.0);
}