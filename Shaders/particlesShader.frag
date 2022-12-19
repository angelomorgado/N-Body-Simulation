#version 460 core

// input variables
in vec3 color;
in vec2 textureCoords;

// output variable
out vec4 fragColor;

uniform sampler2D texture1;

const float Transp = 0.99;

void main() {
    // set the color of the fragment
    // fragColor = vec4(color, 1.0);
    fragColor = texture(texture1, textureCoords);
    // Mix with black as it gets older, to simulate a bit of smoke
    fragColor = vec4(mix( vec3(0,0,0), fragColor.xyz, Transp ), fragColor.a);
    fragColor.a *= Transp;
}