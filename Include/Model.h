#pragma once

#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <Mesh.h>
#include <Shader.h>
#include <Utils.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Material {
    glm::vec3 Diffuse;
    glm::vec3 Specular;
    glm::vec3 Ambient;
    float Shininess;
};

//unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

class Model
{
    public:
	    //================= Attributes =================
        vector<TextureMesh> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        vector<Mesh> meshes;
        string directory;
        bool gammaCorrection;
	    Material model_material;

	    //================ Methods =====================
        // constructor, expects a filepath to a 3D model.
        Model(string const& path, bool gamma = false);

        // draws the model, and thus all its meshes
        void Draw(Shader& shader);
        void Draw(Shader& shader, Material material);
        
        // change the diffuse texture of all meshes in the model
        void changeTexture(const char* name, string dir);

    private:
	    //================ Attributes =================
	    const aiScene* scene;
	
	    //================ Methods ====================
        // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
        void loadModel(string const& path);

        // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
        void processNode(aiNode* node, const aiScene* scene);
	
		// processes a mesh and returns a Mesh object
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	
        // checks all material textures of a given type and loads the textures if they're not loaded yet.
        // the required info is returned as a TextureMesh struct.
        vector<TextureMesh> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

        Material loadMaterial(aiMaterial* mat);

        // Load a texture from file
        GLuint TextureFromFile(const char* path, const string& directory, bool gamma = false);
};

#endif