/*
    Textures.h:

        - Deals with everything related to textures, such as loading textures.
        - It has a special struct that stores every information related to a certain texture
*/

#pragma once

#ifndef TEXTURES_H
#define TEXTURES_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "stb_image.h"

struct Texture {
	unsigned int texture;
	const char* texturePath;
	std::vector<std::string> cubemapFaces;
	int wrapS;
	int wrapT;
	int wrapR;
	int minFilter;
	int magFilter;
    int colorModel;
	int textureNumber;
};

// Loads the texture with the parameters and stores them in tex->texture
void loadTexture(Texture* tex);

void loadCubemap(Texture* tex);

#endif