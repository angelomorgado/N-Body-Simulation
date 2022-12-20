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
#include <Camera.h>
#include <Scene.h>
#include <Textures.h>

struct Particle
{
    glm::vec3 position;
    glm::vec3 velocity;
    float mass;
    float radius;
    glm::vec4 color;
    float size;
    glm::vec4 texCoords;

    // Constructor
    Particle() : position(0.0f), velocity(0.0f), mass(0.0f), radius(0.0f), color(1.0f), size(0.2f), texCoords(0.0f) { }
};

class Particles 
{
public:
    Particles(GLuint nParticles = 1000, float minMass = 0.1f, float maxMass = 1.0f, float minRadius = 0.1f, float maxRadius = 1.5f, float minSpeed = 0.0f, float maxSpeed = 1.0f, float minSize = 0.5f, float maxSize = 2.0f);

    // Draw one particle according to its index in the VAO and its characteristics
    void Draw(Shader shader, Camera camera);

private:
    // Attributes
    GLuint nParticles;
    std::vector<Particle> particles;

    // Attributes
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> velocities;
    std::vector<float> masses;
    std::vector<float> radiuses;
    std::vector<glm::vec3> colors;
    std::vector<float> sizes;
    GLuint spriteTexture;

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
    void getSpriteTexture();
};