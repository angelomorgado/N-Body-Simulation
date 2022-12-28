#include <Particles.h>

Particles::Particles(GLuint nParticles, float minMass, float maxMass, float minRadius, float maxRadius, float minSpeed, float maxSpeed, float minSize, float maxSize){
        this->nParticles = nParticles;
        
        // Get the sprite texture
        getSpriteTexture();

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
            float a = 1.0f;
            this->colors.push_back(glm::vec4(r, g, b, a));
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
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, this->positionBuffer);
        glBufferData(GL_ARRAY_BUFFER, this->nParticles * sizeof(glm::vec3), &this->positions[0], GL_DYNAMIC_DRAW);
        
        // Size
        glBindBuffer(GL_ARRAY_BUFFER, this->sizeBuffer);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, this->sizeBuffer);
        glBufferData(GL_ARRAY_BUFFER, this->nParticles * sizeof(float), &this->sizes[0], GL_DYNAMIC_DRAW);
        
        // Radius
        glBindBuffer(GL_ARRAY_BUFFER, this->radiusBuffer);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, this->radiusBuffer);
        glBufferData(GL_ARRAY_BUFFER, this->nParticles * sizeof(float), &this->radiuses[0], GL_DYNAMIC_DRAW);

        // Color
        glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, this->colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, this->nParticles * sizeof(glm::vec4), &this->colors[0], GL_DYNAMIC_DRAW);

        // Velocity
        glBindBuffer(GL_ARRAY_BUFFER, this->velocityBuffer);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, this->velocityBuffer);
        glBufferData(GL_ARRAY_BUFFER, this->nParticles * sizeof(glm::vec3), &this->velocities[0], GL_DYNAMIC_DRAW);

        // Mass
        glBindBuffer(GL_ARRAY_BUFFER, this->massBuffer);
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, this->massBuffer);
        glBufferData(GL_ARRAY_BUFFER, this->nParticles * sizeof(float), &this->masses[0], GL_DYNAMIC_DRAW);

        glBindVertexArray(0);
    }

void Particles::Draw(Shader shader, Camera camera)
{
    // Enable the shader and set the view, projection, and model matrices
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

    // Bind the sprite texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->spriteTexture);
    shader.setInt("texture1", 0);

    // Enables
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_PROGRAM_POINT_SIZE);

    // Draw
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_POINTS, 0, this->nParticles);

    // Disables
    // glDisable(GL_BLEND);
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

    //Flip the image horizontally
    stbi_set_flip_vertically_on_load(true);

    // Load the image
    int width, height, nrChannels;
    // TODO: FAZER ISTO NAO HARDCODED
    unsigned char* data = stbi_load("Media/Textures/star.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
}