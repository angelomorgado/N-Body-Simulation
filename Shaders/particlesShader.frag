#version 460 core

// input variables
in vec3 color;

// output variable
out vec4 fragColor;

void main() {
    // set the color of the fragment
    fragColor = vec4(color, 1.0);
}