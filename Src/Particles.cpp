#include <Particles.h>

Particles::Particles(GLuint nParticles, float minMass, float maxMass, float minRadius, float maxRadius, float minSpeed, float maxSpeed, float minSize, float maxSize)
{
    this->nParticles = nParticles;

    // Fill the particles vector
    for (int i=0; i<nParticles; i++)
    {
        Particle particle;
        
        // Radius
        particle.radius = rand() / (float)RAND_MAX;
        particle.radius = minRadius + particle.radius * (maxRadius - minRadius);

        // Auxiliar variables
        float theta = 2.0 * glm::pi<float>() * rand() / (float)RAND_MAX;
        float phi = glm::pi<float>() * rand() / (float)RAND_MAX;

        // Position
        particle.position = glm::vec3(
            particle.radius * glm::sin(phi) * glm::cos(theta), // x
            particle.radius * glm::sin(phi) * glm::sin(theta), // y
            particle.radius * glm::cos(phi) // z
        );

        // Velocity
        float vx = rand() / (float)RAND_MAX;
        vx = minSpeed + vx * (maxSpeed - minSpeed);
        float vy = rand() / (float)RAND_MAX;
        vy = minSpeed + vy * (maxSpeed - minSpeed);
        float vz = rand() / (float)RAND_MAX;
        vz = minSpeed + vz * (maxSpeed - minSpeed);
        particle.velocity = glm::vec3(vx, vy, vz);

        // Mass
        particle.mass = rand() / (float)RAND_MAX;
        particle.mass = minMass + particle.mass * (maxMass - minMass);

        // Color
        particle.color = glm::vec3(
            rand() / (float)RAND_MAX, // r
            rand() / (float)RAND_MAX, // g
            rand() / (float)RAND_MAX // b
        );

        // Size
        particle.size = rand() / (float)RAND_MAX;
        particle.size = minSize + particle.size * (maxSize - minSize);

        // Texture coordinates (for the quad) Cant be random
        particle.texCoords = glm::vec4(
            glm::vec2(0.0f, 0.0f), // Bottom left
            glm::vec2(1.0f, 0.0f), // Bottom right
            glm::vec2(1.0f, 1.0f), // Top right
            glm::vec2(0.0f, 1.0f) // Top left
        );

        // Add the particle to the vector
        this->particles.push_back(particle);
    }

    // Bind the VAO
    glBindVertexArray(this->VAO);

    // Bind the VBO and EBO
    glGenBuffers(1, &(this->VBO));
    glGenBuffers(1, &(this->EBO));

    // Bind the VBO and set the vertex data
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->nParticles * sizeof(Particle), &this->particles[0], GL_STATIC_DRAW);

    // Setup the EBO
    std::vector<GLuint> indices(this->nParticles * 6);
    // The vertices for the quad are arranged as follows:
    //
    //   1---3
    //   |   |
    //   0---2
    //
    // Each quad consists of two triangles, with vertices 0, 1, and 2, and vertices 1, 3, and 2.

    // Fill the indices vector
    for (GLuint i = 0; i < this->nParticles; i++)
    {
        indices[i * 6 + 0] = i * 4 + 0;
        indices[i * 6 + 1] = i * 4 + 1;
        indices[i * 6 + 2] = i * 4 + 2;
        indices[i * 6 + 3] = i * 4 + 1;
        indices[i * 6 + 4] = i * 4 + 3;
        indices[i * 6 + 5] = i * 4 + 2;
    }

    // Bind the EBO and set the vertex data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nParticles * 6 * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    // Set up the vertex attributes
    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, position));
    glEnableVertexAttribArray(0);
    
    // Texture coordinates
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, texCoords));
    glEnableVertexAttribArray(1);

    // Color
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, color));
    glEnableVertexAttribArray(2);

    // Size
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, size));
    glEnableVertexAttribArray(3);

    // Mass
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, mass));
    glEnableVertexAttribArray(4);

    // Velocity
    glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, velocity));
    glEnableVertexAttribArray(5);

    // Radius
    glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, radius));
    glEnableVertexAttribArray(6);

    // Unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Load the sprite texture
    getSpriteTexture();
}

void checkForErrors()
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cout << "OpenGL error: " << error << std::endl;
    }
}

void Particles::Draw(Shader shader, Camera camera)
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

    glBindVertexArray(VAO);
    for (unsigned int i = 0; i < this->nParticles; i++) {
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(i * 6 * sizeof(unsigned int)));
    }
    glBindVertexArray(0);
    
}

// Get the sprite texture from the file
void Particles::getSpriteTexture()
{
    glGenTextures(1, &(this->spriteTexture)); // How many textures and where to store them
    glBindTexture(GL_TEXTURE_2D, this->spriteTexture);

    // Wrapping parameters Tex2
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Filtering parameters Tex2
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Load the image
    int width, height, nrChannels;
    unsigned char* data = stbi_load("Media/Textures/star.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
}