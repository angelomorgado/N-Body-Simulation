#include "Textures.h"

void loadTexture(Texture* tex) {
    glGenTextures(1, &tex->texture); // How many textures and where to store them
    glActiveTexture(tex->textureNumber);
    glBindTexture(GL_TEXTURE_2D, tex->texture);

    // Wrapping parameters Tex1
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, tex->wrapS);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tex->wrapT);

    // Filtering parameters Tex1
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tex->minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tex->magFilter);

    // Load and generate the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load(tex->texturePath, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, tex->colorModel, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture " << std::endl;
    }

    stbi_image_free(data);
}

void loadCubemap(Texture* tex) {
    glGenTextures(1, &tex->texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex->texture);

	// Set the parameters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, tex->wrapS);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, tex->wrapT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, tex->wrapR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, tex->minFilter);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, tex->magFilter);

	int width, height, nrChannels;
	
	// Load the 6 textures
    for (unsigned int i = 0; i < tex->cubemapFaces.size(); i++)
	{
		unsigned char* data = stbi_load(tex->cubemapFaces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, tex->colorModel, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << tex->cubemapFaces[i] << std::endl;
			stbi_image_free(data);
		}
	}
}