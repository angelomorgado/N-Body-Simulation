#include <ParticleType.h>

ParticleType getParticleA()
{
    float minRadius = 0.1f;
    float maxRadius = 4.5f;
    float minMass = 1.0f;
    float maxMass = 2.0f;
    float minSize = 0.3f;
    float maxSize = 0.6f;

    // Color
    glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    // Generate random values
    // float radius = minRadius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxRadius - minRadius)));
    float radius = maxRadius;

    // Position
    glm::vec4 position = createPosition(radius);

    // Mass
    float mass = minMass + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxMass - minMass)));

    // Velocity
    glm::vec4 velocity = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // Size
    float size = minSize + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxSize - minSize)));

    return ParticleType(position, velocity, mass, radius, color, size);
}

ParticleType getParticleB()
{
    float minRadius = 0.1f;
    float maxRadius = 4.5f;
    float minMass = 5.0f;
    float maxMass = 10.0f;
    float minSize = 1.0f;
    float maxSize = 2.0f;

    // Color
    glm::vec4 color = glm::vec4(0.68f, 0.768f, 0.153f, 1.0f); // Yellow

    // Generate random values
    // float radius = minRadius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxRadius - minRadius)));
    float radius = maxRadius;

    // Position
    glm::vec4 position = createPosition(radius);

    // Mass
    float mass = minMass + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxMass - minMass)));

    // Velocity
    glm::vec4 velocity = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // Size
    float size = minSize + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxSize - minSize)));

    return ParticleType(position, velocity, mass, radius, color, size);
}

ParticleType getParticleC()
{
    float minRadius = 0.1f;
    float maxRadius = 4.5f;
    float minMass = 20.0f * 1000.0f;
    float maxMass = 25.0f * 1000.0f;
    float minSize = 7.0f;
    float maxSize = 8.0f;

    // Color
    glm::vec4 color = glm::vec4(0.72f, 0.086f, 0.086f, 1.0f);

    // Generate random values
    // float radius = minRadius + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxRadius - minRadius)));
    float radius = maxRadius;

    // Position
    glm::vec4 position = createPosition(radius);

    // Mass
    float mass = minMass + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxMass - minMass)));

    // Velocity
    glm::vec4 velocity = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // Size
    float size = minSize + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxSize - minSize)));

    return ParticleType(position, velocity, mass, radius, color, size);
}

// Auxiliary functions
glm::vec4 createPosition(float radius) {
    float u = rand() / (float)RAND_MAX; //random number between 0 and 1
    float x1 = rand() / (float)RAND_MAX * 2.0 - 1.0; //random number between -1 and 1 for x.x
    float x2 = rand() / (float)RAND_MAX * 2.0 - 1.0; //random number between -1 and 1 for x.y
    float x3 = rand() / (float)RAND_MAX * 2.0 - 1.0; //random number between -1 and 1 for x.z
    float mag = std::max(0.0001f, std::sqrt(x1*x1 + x2*x2 + x3*x3)); //get length of x, avoid being 0
    float inv_mag = 1.0 / mag;
    x1 *= inv_mag; //turn x into a direction through normalization
    x2 *= inv_mag; //turn x into a direction through normalization
    x3 *= inv_mag; //turn x into a direction through normalization
    float c = std::cbrt(u) * radius; //rescale c with a cbrt to make the spherical density exactly uniform
    // glm::vec3 position = glm::vec3(x1*c, x2*c, x3*c); //get a random point by multiplying random position from the centre with a random direction
    return glm::vec4(x1*c, x2*c, x3*c, 1.0f);
}