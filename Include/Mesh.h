#pragma once

#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "stb_image.h"

#include <string>
#include <vector>

#define MAX_BONE_INFLUENCE 4

struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// color
	glm::vec4 Color;
	// useDiffuse
	float useDiffuse;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];
};

struct TextureMesh {
	unsigned int id;
	std::string type; // diffuse, specular, normal, height
	std::string path; 
};

class Mesh {
	public :
		// Mesh data
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<TextureMesh> textures;

		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<TextureMesh> textures);
		void Draw(Shader& shader);
	
	private:
		// Render data
		unsigned int VAO, VBO, EBO;

		// Initializes all the buffer objects/arrays
		void setupMesh();
};

#endif