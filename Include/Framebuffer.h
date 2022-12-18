/*
    Framebuffer.h:

        - It implements a framebuffer object that can be used to render to a texture.
        - It also implements a quad that can be used to draw the texture to the screen.
        - To use it, you need to bind it, draw to it, then unbind it, and lastly draw the quad, all inside the main loop.
*/

#pragma once

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <Utils.h>
#include <Shader.h>

struct Framebuffer_obj{
	GLuint fbo;
	GLuint rbo;
	GLuint textureColorBuffer;
};


class Framebuffer {
public:
    Framebuffer();
    void bind();
    void unbind();
    void drawQuad(Shader screenShader);

private:
    // Framebuffer data
    GLuint fbo;
    GLuint rbo;
    GLuint textureColorBuffer;
	GLuint quadVAO, quadVBO;
	
    void initializeQuad();
};

#endif // !FRAMEBUFFER_H