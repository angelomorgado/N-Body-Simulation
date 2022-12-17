#version 460 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec3 LightPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
	
	//Normal = view * aNormal; 
	Normal =  mat3(transpose(inverse(view * model))) * aNormal; // Very costly but better with scaling

	// Position of the fragment can be found by multuplying the model matrix with the vertex position
	FragPos = vec3(view * model * vec4(aPos, 1.0));

	LightPos = vec3(view * vec4(lightPos, 1.0)); // Transform the light position to view space
}