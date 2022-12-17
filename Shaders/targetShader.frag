#version 460 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

//uniform vec4 multiplyColor;
uniform sampler2D texture1;

uniform vec3 objectColor;

uniform Material material;
uniform Light light; 


void main(){
	// texture
	vec4 texture = texture(texture1, TexCoord);
	
	// ambient
	vec3 ambient = material.ambient * light.ambient;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0); // we use the max so that the diffuse component is never negative
	vec3 diffuse = (diff * material.diffuse) * light.diffuse;

	// specular
	vec3  viewDir = normalize(-FragPos); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
	vec3  reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = material.specular * spec * light.specular;

	vec3 result = (ambient + diffuse + specular) * objectColor;
	
	FragColor = vec4(result, 1.0) * texture;
}