#include <Particles.h>

std::vector<glm::vec4> readVerticesFromFile(const std::string& filePath) {
    std::vector<glm::vec4> vertices;

    // Open the file using C-style file I/O
    FILE* file = fopen(filePath.c_str(), "r");
    if (file == nullptr) {
        // Handle error
    }

    // Read the file in blocks of 4KB
    const size_t blockSize = 4096;
    char block[blockSize];
    size_t numVertices = 0;
    while (fgets(block, blockSize, file) != nullptr) {
        // Split the block on newline characters
        char* line = block;
        while (line != nullptr) {
            // Split the line on spaces
            glm::vec4 vertex;
            vertex.x = std::strtod(line, &line);
            if (line == nullptr) break;
            vertex.y = std::strtod(line, &line);
            if (line == nullptr) break;
            vertex.z = std::strtod(line, &line);
            vertex.w = 1;

            // Add the vertex to the list
            if (numVertices < vertices.size()) {
                vertices[numVertices] = vertex;
            } else {
                vertices.push_back(vertex);
            }
            ++numVertices;

            // Move to the next line
            line = strchr(line, '\n');
            if (line != nullptr) ++line;
        }
    }

    // Close the file
    fclose(file);

    // Trim the vector to the actual number of vertices
    vertices.resize(numVertices);

    return vertices;
}

Particles::Particles(GLuint nParticles, std::string texture_path, std::string point_cloud_path, float minMass, float maxMass, float minRadius, float maxRadius, float minSpeed, float maxSpeed, float minSize, float maxSize)
{
    this->positions_2 = readVerticesFromFile(point_cloud_path);
    generateValues(nParticles, minMass, maxMass, minRadius, maxRadius, minSpeed, maxSpeed, minSize, maxSize, false);
    transferDataToGPU();
    texture = new Texture(texture_path);
}

Particles::Particles(GLuint nParticles, std::string texture_path)
{
    this->nParticles = nParticles;
    groupValues();
    transferDataToGPU();
    texture = new Texture(texture_path);
}

void Particles::Draw(Shader shader, Camera camera)
{
    // Enable the shader and set the view, projection, and model matrices
    shader.use();
    setView(&shader, camera.GetViewMatrix());
    setProjection(&shader, glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    setModel(
        &shader, // shader
        glm::vec3(0.0f, 0.0f, 0.0f), // translation
        glm::vec3(1.0f, 0.0f, 0.0f), // rotation axis
        0.0f, // rotation angle
        glm::vec3(1.0f) // scale
    );

    // Bind the sprite texture
    texture->bind();
    shader.setInt("texture1", texture->textureNumber);

    // Enables
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    // Draw
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_POINTS, 0, this->nParticles);

    // Disables
    // glDisable(GL_BLEND);
}

void Particles::groupValues()
{
    float probA = 0.9, probB = 0.09, probC = 0.01;
    for (GLuint i = 0; i < nParticles; i++)
    {
        ParticleType type;

        if (i < nParticles * probA)
        {
            type = getParticleA();
        }
        else if (i < nParticles * (1 - probC))
        {
            type = getParticleB();
        }
        else
        {
            type = getParticleC();
        }

        this->positions.push_back(type.position);
        this->radiuses.push_back(type.radius);
        this->velocities.push_back(type.velocity);
        this->masses.push_back(type.mass);
        this->sizes.push_back(type.size);
        this->colors.push_back(type.color);
    }
}

void Particles::generateValues(GLuint nParticles, float minMass, float maxMass, float minRadius, float maxRadius, float minSpeed, float maxSpeed, float minSize, float maxSize, bool sphere)
{
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
        float x, y, z, w;
        if (sphere){
            x = radius * glm::sin(phi) * glm::cos(theta);
            y = radius * glm::sin(phi) * glm::sin(theta);
            z = radius * glm::cos(phi);
            w = 1.0f;
        }
        else{
            x = minRadius + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxRadius - minRadius)));
            y = minRadius + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxRadius - minRadius)));
            z = minRadius + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxRadius - minRadius)));
            w = 1.0f;
        }

        this->positions.push_back(glm::vec4(x, y, z, w));

        // Velocity
        float vx = rand() / (float)RAND_MAX;
        float vy = rand() / (float)RAND_MAX;
        float vz = rand() / (float)RAND_MAX;
        vx = minSpeed + vx * (maxSpeed - minSpeed);
        vy = minSpeed + vy * (maxSpeed - minSpeed);
        vz = minSpeed + vz * (maxSpeed - minSpeed);
        this->velocities.push_back(glm::vec4(vx, vy, vz, w));

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
}

void Particles::transferDataToGPU()
{
    // Initialize the buffers
    glGenBuffers(1, &this->positionBuffer);
    glGenBuffers(1, &this->velocityBuffer);
    glGenBuffers(1, &this->massBuffer);
    glGenBuffers(1, &this->radiusBuffer);
    glGenBuffers(1, &this->colorBuffer);
    glGenBuffers(1, &this->sizeBuffer);
    glGenBuffers(1, &this->position_2Buffer);

    // Initialize the VAO
    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);
    
    // Position
    glBindBuffer(GL_ARRAY_BUFFER, this->positionBuffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, this->positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, this->nParticles * sizeof(glm::vec4), &this->positions[0], GL_DYNAMIC_DRAW);
    
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
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, this->velocityBuffer);
    glBufferData(GL_ARRAY_BUFFER, this->nParticles * sizeof(glm::vec4), &this->velocities[0], GL_DYNAMIC_DRAW);

    // Mass
    glBindBuffer(GL_ARRAY_BUFFER, this->massBuffer);
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, this->massBuffer);
    glBufferData(GL_ARRAY_BUFFER, this->nParticles * sizeof(float), &this->masses[0], GL_DYNAMIC_DRAW);

    // Position 2
    glBindBuffer(GL_ARRAY_BUFFER, this->position_2Buffer);
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 6, this->position_2Buffer);
    glBufferData(GL_ARRAY_BUFFER, this->nParticles * sizeof(glm::vec3), &this->positions_2[0], GL_DYNAMIC_DRAW);

    glBindVertexArray(0);
}