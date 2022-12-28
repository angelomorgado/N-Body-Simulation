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
#include <Texture2D.h>

class Particles 
{
public:
    Particles(GLuint nParticles = 1000, std::string texture_path = "Media/Textures/star.png", float minMass = 0.1f, float maxMass = 1.0f, float minRadius = 0.1f, float maxRadius = 1.5f, float minSpeed = 0.0f, float maxSpeed = 1.0f, float minSize = 0.5f, float maxSize = 2.0f);

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
    void transferDataToGPU();
};