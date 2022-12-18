/*
    Particles.h:

        - It implements a class that stores all the information related to all particles, including their position, velocity, mass, etc.
*/
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Particles 
{
public:
    Particles(GLuint nParticles, float minMass, float maxMass, float minRadius, float maxRadius, float minSpeed, float maxSpeed){
        this->nParticles = nParticles;
        
        // Initialize the particles
        for (int i = 0; i < nParticles; i++)
        {
            // Position
            float x = (rand() % 1000) / 1000.0f;
            float y = (rand() % 1000) / 1000.0f;
            float z = (rand() % 1000) / 1000.0f;
            this->positions.push_back(glm::vec3(x, y, z));

            // Velocity
            float vx = (rand() % 1000) / 1000.0f;
            float vy = (rand() % 1000) / 1000.0f;
            float vz = (rand() % 1000) / 1000.0f;
            this->velocities.push_back(glm::vec3(vx, vy, vz));

            // Mass
            float mass = (rand() % 1000) / 1000.0f;
            mass = minMass + mass * (maxMass - minMass);
            this->masses.push_back(mass);

            // Radius
            float radius = (rand() % 1000) / 1000.0f;
            radius = minRadius + radius * (maxRadius - minRadius);
            this->radiuses.push_back(radius);

            // Color
            float r = (rand() % 1000) / 1000.0f;
            float g = (rand() % 1000) / 1000.0f;
            float b = (rand() % 1000) / 1000.0f;
            this->colors.push_back(glm::vec3(r, g, b));
        }

        // Initialize the buffers
        glGenBuffers(1, &this->positionBuffer);
        glGenBuffers(1, &this->velocityBuffer);
        glGenBuffers(1, &this->massBuffer);
        glGenBuffers(1, &this->radiusBuffer);
        glGenBuffers(1, &this->colorBuffer);

        // Initialize the VAO
        glGenVertexArrays(1, &this->VAO);
        glBindVertexArray(this->VAO);
        
        // Position
        glBindBuffer(GL_ARRAY_BUFFER, this->positionBuffer);
        glBufferData(GL_ARRAY_BUFFER, this->nParticles * sizeof(glm::vec3), &this->positions[0], GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        // Velocity
        glBindBuffer(GL_ARRAY_BUFFER, this->velocityBuffer);
        glBufferData(GL_ARRAY_BUFFER, this->nParticles * sizeof(glm::vec3), &this->velocities[0], GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        // Mass
        glBindBuffer(GL_ARRAY_BUFFER, this->massBuffer);
        glBufferData(GL_ARRAY_BUFFER, this->nParticles * sizeof(float), &this->masses[0], GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);

        // Radius
        glBindBuffer(GL_ARRAY_BUFFER, this->radiusBuffer);
        glBufferData(GL_ARRAY_BUFFER, this->nParticles * sizeof(float), &this->radiuses[0], GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);

        // Color
        glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, this->nParticles * sizeof(glm::vec3), &this->colors[0], GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glBindVertexArray(0);
    }

    // Draw one particle according to its index in the VAO and its characteristics
    void Draw()
    {
        glBindVertexArray(this->VAO);
        glDrawArrays(GL_POINTS, 0, this->nParticles);
        glBindVertexArray(0);
    }

private:
    GLuint nParticles;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> velocities;
    std::vector<float> masses;
    std::vector<float> radiuses;
    std::vector<glm::vec3> colors;

    GLuint positionBuffer;
    GLuint velocityBuffer;
    GLuint massBuffer;
    GLuint radiusBuffer;
    GLuint colorBuffer;

    GLuint VAO;
};