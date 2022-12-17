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