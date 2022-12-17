#version 330 core

in vec3 TexCoords; // direction of the texture

out vec4 FragColor;

uniform samplerCube skybox; // cubemap texture sampler

void main() {
	FragColor = texture(skybox, TexCoords);
}