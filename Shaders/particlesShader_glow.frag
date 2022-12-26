#version 460 core

// input variables
in vec3 vColor;
in vec2 texCoord;

// output variable
out vec4 fragColor;

uniform sampler2D texture1;

float emissionStrength = 0.5;

void main() {
    vec4 tex = texture(texture1, texCoord);
    vec4 emission = vec4(vColor * emissionStrength, 1.0);
    if (tex.a < 0.1) {
        tex.a = 0.01;
        emission = vec4(1.0, 1.0, 1.0, 0.1);
    }
    fragColor = tex * emission;
}