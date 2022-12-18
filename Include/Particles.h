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
#include <Shader.h>

class Particles 
{
public:
    Particles(GLuint nParticles, float minMass, float maxMass, float minRadius, float maxRadius, float minSpeed, float maxSpeed, float minSize, float maxSize){
        this->nParticles = nParticles;
        
        // Initialize the particles
        for (int i = 0; i < nParticles; i++)
        {
            // Radius of the particle
            float radius = rand() / (float)RAND_MAX;
            radius = minRadius + radius * (maxRadius - minRadius);

            // Auxiliar variables to calculate the position
            float theta = 2.0 * glm::pi<float>() * rand() / (float)RAND_MAX;
            float phi = glm::pi<float>() * rand() / (float)RAND_MAX;

            // Position - Random position that form a sphere
            float x = radius * glm::sin(phi) * glm::cos(theta);
            float y = radius * glm::sin(phi) * glm::sin(theta);
            float z = radius * glm::cos(phi);
            this->positions.push_back(glm::vec3(x, y, z));

            // Velocity
            float vx = rand() / (float)RAND_MAX;
            float vy = rand() / (float)RAND_MAX;
            float vz = rand() / (float)RAND_MAX;
            vx = minSpeed + vx * (maxSpeed - minSpeed);
            vy = minSpeed + vy * (maxSpeed - minSpeed);
            vz = minSpeed + vz * (maxSpeed - minSpeed);
            this->velocities.push_back(glm::vec3(vx, vy, vz));

            // Mass
            float mass = rand() / (float)RAND_MAX;
            mass = minMass + mass * (maxMass - minMass);
            this->masses.push_back(mass);

            // Size
            float size = rand() / (float)RAND_MAX;
            size = minSize + size * (maxSize - minSize);
            this->sizes.push_back(size);

            // Color (the RGB values are between 0 and 1)
            float r = rand() / (float)RAND_MAX;
            float g = rand() / (float)RAND_MAX;
            float b = rand() / (float)RAND_MAX;
            this->colors.push_back(glm::vec3(r, g, b));
        }

        // Initialize the buffers
        glGenBuffers(1, &this->positionBuffer);
        glGenBuffers(1, &this->velocityBuffer);
        glGenBuffers(1, &this->massBuffer);
        glGenBuffers(1, &this->radiusBuffer);
        glGenBuffers(1, &this->colorBuffer);
        glGenBuffers(1, &this->sizeBuffer);


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

        // Size
        glBindBuffer(GL_ARRAY_BUFFER, this->sizeBuffer);
        glBufferData(GL_ARRAY_BUFFER, this->nParticles * sizeof(float), &this->sizes[0], GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glBindVertexArray(0);
    }

    // Draw one particle according to its index in the VAO and its characteristics
    void Draw(Shader shader, Camera camera)
    {
        shader.use();
        setView(&shader, camera.GetViewMatrix());
		setProjection(&shader, glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        setModel(
            &shader, // shader
            glm::vec3(0.0f, 1.0f, 0.0f), // translation
            glm::vec3(1.0f, 0.0f, 0.0f), // rotation axis
            0.0f, // rotation angle
            glm::vec3(1.0f) // scale
        );

        glEnable(GL_PROGRAM_POINT_SIZE);
        glBindVertexArray(this->VAO);
        glDrawArrays(GL_POINTS, 0, this->nParticles);
        glBindVertexArray(0);
    }

private:
    // Attributes
    GLuint nParticles;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> velocities;
    std::vector<float> masses;
    std::vector<float> radiuses;
    std::vector<glm::vec3> colors;
    std::vector<float> sizes;

    // Buffers
    GLuint positionBuffer;
    GLuint velocityBuffer;
    GLuint massBuffer;
    GLuint radiusBuffer;
    GLuint colorBuffer;
    GLuint sizeBuffer;

    // VAO
    GLuint VAO;
};