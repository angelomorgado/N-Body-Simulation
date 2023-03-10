#version 460 core

// input variables
in vec4 vColor;
in vec2 texCoord;

// output variable
out vec4 fragColor;

uniform sampler2D texture1;

void main() {
    vec4 tex = texture(texture1, texCoord);
    if (tex.a < 0.1) {
        discard;
    }
    fragColor = vColor * tex;
}