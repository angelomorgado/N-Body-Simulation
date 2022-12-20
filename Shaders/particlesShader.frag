#version 450 core

// input variables
in vec3 color;
in vec2 textureCoords;

// output variable
out vec4 fragColor;

uniform sampler2D texture1;

void main() {
    // set the color of the fragment
    // fragColor = vec4(color, 1.0);
    fragColor = texture(texture1, textureCoords[gl_VertexID % 4]) * vec4(color, 1.0);
}