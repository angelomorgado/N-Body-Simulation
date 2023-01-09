#pragma once

#ifndef PARTICLE_TYPE_H
#define PARTICLE_TYPE_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

struct ParticleType
{
    glm::vec4 position;
    glm::vec4 velocity;
    float mass;
    float radius;
    glm::vec4 color;
    float size;

    // Constructor
    ParticleType() 
    {
        this->position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        this->velocity = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        this->mass = 1.0f;
        this->radius = 1.0f;
        this->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        this->size = 1.0f;
    }

    ParticleType(glm::vec4 position, glm::vec4 velocity, float mass, float radius, glm::vec4 color, float size)
    {
        this->position = position;
        this->velocity = velocity;
        this->mass = mass;
        this->radius = radius;
        this->color = color;
        this->size = size;
    }
};

ParticleType getParticleA();
ParticleType getParticleB();
ParticleType getParticleC();

glm::vec4 createPosition(float radius);

#endif