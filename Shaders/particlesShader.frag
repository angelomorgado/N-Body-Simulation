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
    vec4 tex = texture(texture1, texCoord);
    if (tex.a < 1.0) {
        discard;
    }
    fragColor = tex * vec4(vColor, 1.0);
}