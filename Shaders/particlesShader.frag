#version 450 core

// input variables
in vec3 vColor;
in vec2 texCoord;

// output variable
out vec4 fragColor;

uniform sampler2D texture1;

void main() {
    // set the color of the fragment
    // fragColor = vec4(vColor, 1.0);
    fragColor = texture(texture1, texCoord);// * vec4(vColor, 1.0);
}