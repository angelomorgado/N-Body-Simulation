#version 450 core

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
out vec2 textureCoords;

// uniform variables
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//const vec2 texCoords[] = vec2[](vec2(0,0), vec2(1,0), vec2(1,1), vec2(0,0), vec2(1,1), vec2(0,1));

void main() {
    // set the texture coordinates of the particle
    textureCoords[0] = texCoords.xy;
    textureCoords[1] = texCoords.zw;

    // set the color of the particle
    color = vertexColor;

    // set the size of the particle
    gl_PointSize = vertexSize;

    // transform the vertex position using the model-view and projection matrices
    gl_Position = projection * view * model * vec4(vertexPosition, 1.0);
}