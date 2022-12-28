#include "Textures.h"

Texture::Texture(std::string texturePath, int wrapS, int wrapT , int minFilter , int magFilter , int colorModel , int textureNumber) 
{
    this->id = 0;
    this->texturePath = texturePath;
    this->wrapS = wrapS;
    this->wrapT = wrapT;
    this->minFilter = minFilter;
    this->magFilter = magFilter;
    this->colorModel = colorModel;
    this->textureNumber = textureNumber;
    loadTexture();
}

Texture::Texture(std::vector<std::string> cubemapFaces, int wrapS , int wrapT , int minFilter , int magFilter , int colorModel , int textureNumber)
{
    this->id = 0;
    this->cubemapFaces = cubemapFaces;
    this->wrapS = wrapS;
    this->wrapT = wrapT;
    this->minFilter = minFilter;
    this->magFilter = magFilter;
    this->colorModel = colorModel;
    this->textureNumber = textureNumber;
    loadCubemap();
}

void Texture::loadTexture() {
    glGenTextures(1, &id); // How many textures and where to store them
    glActiveTexture(textureNumber);
    glBindTexture(GL_TEXTURE_2D, id);

    // Wrapping parameters Tex1
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);

    // Filtering parameters Tex1
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

    // Load and generate the texture
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, colorModel, width, height, 0, colorModel, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture " << texturePath << std::endl;
    }

    stbi_image_free(data);
}

void Texture::loadCubemap() {
    glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);

	// Set the parameters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, wrapR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, magFilter);

	int width, height, nrChannels;
	
	// Load the 6 textures
    for (unsigned int i = 0; i < cubemapFaces.size(); i++)
	{
		unsigned char* data = stbi_load(cubemapFaces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, colorModel, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << cubemapFaces[i] << std::endl;
			stbi_image_free(data);
		}
	}
}

void Texture::bind()
{
    glActiveTexture(textureNumber);
    glBindTexture(GL_TEXTURE_2D, id);
}