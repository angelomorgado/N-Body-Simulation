#version 460 core

// input variables
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexVelocity;
layout (location = 2) in float vertexMass;
layout (location = 3) in float vertexRadius;
layout (location = 4) in vec3 vertexColor;
layout (location = 5) in float vertexSize;

// output variables
out vec3 color;

// uniform variables
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    // Get the index of the current particle
    int index = gl_VertexID;

    // set the color of the particle
    color = vertexColor;

    // set the size of the particle
    gl_PointSize = vertexSize;

    // transform the vertex position using the model-view and projection matrices
    gl_Position = projection * view * model * vec4(vertexPosition, 1.0);
}