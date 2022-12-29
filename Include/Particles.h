/*
    Particles.h:

        - It implements a class that stores all the information related to all particles, including their position, velocity, mass, etc.
*/
#pragma once

#ifndef PARTICLES_H
#define PARTICLES_H

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Shader.h>
#include <Camera.h>
#include <Scene.h>
#include <Textures.h>
#include <ParticleType.h>

class Particles 
{
public:
    Particles(GLuint nParticles, std::string texture_path, float minMass, float maxMass, float minRadius, float maxRadius, float minSpeed, float maxSpeed, float minSize, float maxSize);
    Particles(GLuint nParticles, std::string texture_path);

    // Draw one particle according to its index in the VAO and its characteristics
    void Draw(Shader shader, Camera camera);

private:
    // Attributes
    GLuint nParticles;

    // Attributes
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> velocities;
    std::vector<float> masses;
    std::vector<float> radiuses;
    std::vector<glm::vec4> colors;
    std::vector<float> sizes;
    GLuint spriteTexture;
    Texture *texture;

    // Buffers
    GLuint positionBuffer;
    GLuint velocityBuffer;
    GLuint massBuffer;
    GLuint radiusBuffer;
    GLuint colorBuffer;
    GLuint sizeBuffer;

    // VAO
    GLuint VAO;

    // Functions
    void getSpriteTexture(char* texture_path);
    void generateValues(GLuint nParticles, float minMass, float maxMass, float minRadius, float maxRadius, float minSpeed, float maxSpeed, float minSize, float maxSize);
    void groupValues();
    void transferDataToGPU();
};

#endif