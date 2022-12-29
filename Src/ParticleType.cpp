#include <ParticleType.h>

ParticleType getParticleA()
{
    float minRadius = 0.1f;
    float maxRadius = 1.5f;
    float minMass = 1.0f;
    float maxMass = 2.0f;
    float minVelocity = 3.0f;
    float maxVelocity = 5.0f;
    float minSize = 0.3f;
    float maxSize = 0.6f;

    // Color
    glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    // Generate random values
    float radius = minRadius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxRadius - minRadius)));

    // Position
    float positionX = minRadius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxRadius - minRadius)));
    float positionY = minRadius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxRadius - minRadius)));
    float positionZ = minRadius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxRadius - minRadius)));
    glm::vec3 position = glm::vec3(positionX, positionY, positionZ);

    // Mass
    float mass = minMass + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxMass - minMass)));

    // Velocity
    float velocityX = minVelocity + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxVelocity - minVelocity)));
    float velocityY = minVelocity + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxVelocity - minVelocity)));
    float velocityZ = minVelocity + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxVelocity - minVelocity)));
    glm::vec3 velocity = glm::vec3(velocityX, velocityY, velocityZ);

    // Size
    float size = minSize + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxSize - minSize)));

    return ParticleType(position, velocity, mass, radius, color, size);
}

ParticleType getParticleB()
{
    float minRadius = 0.1f;
    float maxRadius = 1.5f;
    float minMass = 5.0f;
    float maxMass = 10.0f;
    float minVelocity = 2.0f;
    float maxVelocity = 4.0f;
    float minSize = 1.0f;
    float maxSize = 2.0f;

    // Color
    glm::vec4 color = glm::vec4(0.68f, 0.768f, 0.153f, 1.0f); // Yellow

    // Generate random values
    float radius = minRadius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxRadius - minRadius)));

    // Position
    float positionX = minRadius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxRadius - minRadius)));
    float positionY = minRadius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxRadius - minRadius)));
    float positionZ = minRadius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxRadius - minRadius)));
    glm::vec3 position = glm::vec3(positionX, positionY, positionZ);

    // Mass
    float mass = minMass + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxMass - minMass)));

    // Velocity
    float velocityX = minVelocity + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxVelocity - minVelocity)));
    float velocityY = minVelocity + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxVelocity - minVelocity)));
    float velocityZ = minVelocity + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxVelocity - minVelocity)));
    glm::vec3 velocity = glm::vec3(velocityX, velocityY, velocityZ);

    // Size
    float size = minSize + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxSize - minSize)));

    return ParticleType(position, velocity, mass, radius, color, size);
}

ParticleType getParticleC()
{
    float minRadius = 0.1f;
    float maxRadius = 1.5f;
    float minMass = 20.0f;
    float maxMass = 25.0f;
    float minVelocity = 1.0f;
    float maxVelocity = 3.0f;
    float minSize = 3.0f;
    float maxSize = 4.0f;

    // Color
    glm::vec4 color = glm::vec4(0.72f, 0.086f, 0.086f, 1.0f);

    // Generate random values
    float radius = minRadius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxRadius - minRadius)));

    // Position
    float positionX = minRadius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxRadius - minRadius)));
    float positionY = minRadius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxRadius - minRadius)));
    float positionZ = minRadius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxRadius - minRadius)));
    glm::vec3 position = glm::vec3(positionX, positionY, positionZ);

    // Mass
    float mass = minMass + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxMass - minMass)));

    // Velocity
    float velocityX = minVelocity + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxVelocity - minVelocity)));
    float velocityY = minVelocity + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxVelocity - minVelocity)));
    float velocityZ = minVelocity + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxVelocity - minVelocity)));
    glm::vec3 velocity = glm::vec3(velocityX, velocityY, velocityZ);

    // Size
    float size = minSize + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxSize - minSize)));

    return ParticleType(position, velocity, mass, radius, color, size);
}