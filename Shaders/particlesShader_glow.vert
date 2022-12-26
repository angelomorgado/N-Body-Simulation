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

float time = 0.1; // elapsed time in seconds
float noiseScale = 0.5; // scale of the noise function

void main() {
    vSize = vertexSize / 40.0f;

    // Modify the position of the vertex based on noise
    vec3 noise = vec3(
        sin(vertexPosition.x * noiseScale + time),
        sin(vertexPosition.y * noiseScale + time),
        sin(vertexPosition.z * noiseScale + time)
    );

    // Add the noise to the position of the vertex
    pos = vertexPosition + noise;

    // set the color of the particle
    color = vertexColor;

    // transform the vertex position using the model-view and projection matrices
    gl_Position = view * model * vec4(pos, 1.0);
}