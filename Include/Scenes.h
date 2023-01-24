#include "Shader.h"
#include "ComputeShader.h"
#include "Camera.h"
#include "Utils.h"
#include "Callbacks.h"
#include "Scene.h"
#include "Textures.h"
#include "Model.h"
#include "Skybox.h"
#include "Framebuffer.h"
#include "Particles.h"

#define PARTICLE_TEXTURE_PATH "Media/Textures/star.png" // Texture of the particles
#define SKYBOX_PATH "Media/Skyboxes/skybox_galaxy/" // Texture to the skybox
// Camera camera;
CameraPos cameraPos;


void renderScene_PointCloud(Camera* camera, GLFWwindow* window)
{
    GLuint nParticles = 1000000;

    // Shaders
    Shader skyboxShader("Shaders/skyboxShader.vert", "Shaders/skyboxShader.frag");
    Shader particleShader("Shaders/particlesShader.vert", "Shaders/particlesShader.frag", "Shaders/particlesShader.geom");
    ComputeShader point_cloud("Shaders/Compute/particle_shader_h.comp");

    // Skybox
    Skybox skybox(SKYBOX_PATH);

    std::string path[2] = {"Media/PointClouds/rose_1M.txt", "Media/PointClouds/boat_1M.txt"};

    // Particles
    Particles particles(
        nParticles,// Number of particles
        PARTICLE_TEXTURE_PATH, // Texture of the particles
        path,      
        1.0f, // Minimum mass of the particles
        100.0f, // Maximum mass of the particles
        0.1f, // Minimum radius of the particles
        1.5f, // Maximum radius of the particles
        0.0f, // Minimum speed of the particles
        0.0f, // Maximum speed of the particles
        0.2f, // Minimum size of the particles
        0.8f // Maximum size of the particles
    );

    processCallbacks(window, camera, &cameraPos);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Update camera speed
        camera->updateDeltaTime();

        // input
        processInput(window, camera);

        // render
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw particles
        point_cloud.use();
        point_cloud.setFloat("deltaTime", camera->deltaTime);
        point_cloud.execute(nParticles / 64);
        if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS){
            // boat
            point_cloud.setInt("option", 10);
        }
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
            // rose
            point_cloud.setInt("option", 20);
        }
        if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS){
            // sphere
            point_cloud.setInt("option", 30);
        }

        particles.Draw(particleShader, *camera);


        // Draw the Skybox 
        skybox.Draw(skyboxShader, *camera);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void renderScene_Physics(Camera* camera, GLFWwindow* window)
{
    GLuint nParticles = 10240;
    float forceMultiplier = 1.0f;
    float massMultiplier = 1.0f;

    // Shaders
    Shader skyboxShader("Shaders/skyboxShader.vert", "Shaders/skyboxShader.frag");
    Shader particleShader("Shaders/particlesShader.vert", "Shaders/particlesShader.frag", "Shaders/particlesShader.geom");
    ComputeShader physicsShader("Shaders/Compute/particle_shader_physics.comp");

    // Skybox
    Skybox skybox(SKYBOX_PATH);

    // Particles
    Particles particles(
        nParticles, // Number of particles
        PARTICLE_TEXTURE_PATH // Texture of the particles
    );

    processCallbacks(window, camera, &cameraPos);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Update camera speed
        camera->updateDeltaTime();

        // input
        processInput(window, camera);

        // render
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Input
        // Force Multiplier
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
            forceMultiplier += 1.0f;
            cout << "Force multiplier: " << forceMultiplier << std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
            forceMultiplier -= 1.0f;
            cout << "Force multiplier: " << forceMultiplier << std::endl;
        }

        // Mass Multiplier
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
            massMultiplier *= 1.1f;
            cout << "mass multiplier: " << massMultiplier << std::endl;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
            massMultiplier /= 1.1f;
            cout << "mass multiplier: " << massMultiplier << std::endl;
        }

        // Draw particles
        physicsShader.use();
        physicsShader.setFloat("deltaTime", camera->deltaTime);
        physicsShader.setFloat("forceMultiplier", forceMultiplier);
        physicsShader.setFloat("massMultiplier", massMultiplier);
        physicsShader.execute(nParticles / 64);
        particles.Draw(particleShader, *camera);

        // Draw the Skybox 
        skybox.Draw(skyboxShader, *camera);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void renderScene_SimpleBlackHole(Camera* camera, GLFWwindow* window)
{
    GLuint nParticles = 10240;

    // Shaders
    Shader objectShader("Shaders/targetShader.vert", "Shaders/targetShader.frag");
    Shader skyboxShader("Shaders/skyboxShader.vert", "Shaders/skyboxShader.frag");
    Shader particleShader("Shaders/particlesShader.vert", "Shaders/particlesShader.frag", "Shaders/particlesShader.geom");
    ComputeShader blackHoleSimpleShader("Shaders/Compute/particle_shader_black_hole.comp");

    // Skybox
    Skybox skybox(SKYBOX_PATH);
    Model kirby("Media/Objects/kirby.obj");

    // Object
    objectShader.use();
    objectShader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
    objectShader.setVec3("light.position", 1.0f, 5.0f, 1.0f);
    objectShader.setVec3("light.ambient", 0.6f, 0.6f, 0.6f);
    objectShader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
    objectShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    objectShader.setVec3("material.ambient", glm::vec3(1.0f));
    objectShader.setVec3("material.diffuse", glm::vec3(0.6f));
    objectShader.setVec3("material.specular", glm::vec3(0.6f));
    objectShader.setFloat("material.shininess", 0.6f);

    // Particles
    Particles particles(
        nParticles, // Number of particles
        PARTICLE_TEXTURE_PATH // Texture of the particles
    );

    // Variables
    glm::vec3 kirby1Pos = glm::vec3(0.0f,0.0f,0.0f);
    float kirby1Force = 1000.0f;

    processCallbacks(window, camera, &cameraPos);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Update camera speed
        camera->updateDeltaTime();

        // input
        processInput(window, camera);

        // render
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw the kirby
        objectShader.use();
        setView(&objectShader, camera->GetViewMatrix());
        setProjection(&objectShader, glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        setModel(
            &objectShader, // shader
            kirby1Pos, // translation
            glm::vec3(0.0f, 1.0f, 0.0f), // rotation axis
            220.0f, // rotation angle
            glm::vec3(0.10f) // scale
        );
        kirby.Draw(objectShader);

        // Draw particles
        blackHoleSimpleShader.use();
        blackHoleSimpleShader.setFloat("first_g_force", kirby1Force);
        blackHoleSimpleShader.execute(nParticles / 64);
        particles.Draw(particleShader, *camera);

        // Draw the Skybox 
        skybox.Draw(skyboxShader, *camera);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void renderScene_ComplexBlackHole(Camera* camera, GLFWwindow* window)
{
    GLuint nParticles = 10240;

    // Shaders
    Shader objectShader("Shaders/targetShader.vert", "Shaders/targetShader.frag");
    Shader skyboxShader("Shaders/skyboxShader.vert", "Shaders/skyboxShader.frag");
    Shader particleShader("Shaders/particlesShader.vert", "Shaders/particlesShader.frag", "Shaders/particlesShader.geom");
    ComputeShader blackHoleComplexShader("Shaders/Compute/particle_shader_black_hole_movement.comp");

    // Skybox
    Skybox skybox(SKYBOX_PATH);
    Model kirby("Media/Objects/kirby.obj");

    // Object
    objectShader.use();
    objectShader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
    objectShader.setVec3("light.position", 1.0f, 5.0f, 1.0f);
    objectShader.setVec3("light.ambient", 0.6f, 0.6f, 0.6f);
    objectShader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
    objectShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    objectShader.setVec3("material.ambient", glm::vec3(1.0f));
    objectShader.setVec3("material.diffuse", glm::vec3(0.6f));
    objectShader.setVec3("material.specular", glm::vec3(0.6f));
    objectShader.setFloat("material.shininess", 0.6f);

    // Particles
    Particles particles(
        nParticles, // Number of particles
        PARTICLE_TEXTURE_PATH, // Texture of the particles
        2.0f, // Min Mass of the particles
        4.0f, // Max Mass of the particles
        0.1f, // Min Radius of the particles
        4.5f, // Max Radius of the particles
        -1.0f, // Min Speed of the particles
        1.0f, // Max Speed of the particles
        1.0f, // Min Size of the particles
        2.0f // Max Size of the particles
    );

    // Variables
    glm::vec3 kirby1Pos = glm::vec3(-5.0f,0.0f,0.0f);
    float kirby1Force = 3000.0f;
    glm::vec3 kirby2Pos = glm::vec3(5.0f,0.0f,0.0f);
    float kirby2Force = 3000.0f;

    processCallbacks(window, camera, &cameraPos);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Update camera speed
        camera->updateDeltaTime();

        // input
        processInput(window, camera);

        // render
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw the first kirby
        objectShader.use();
        setView(&objectShader, camera->GetViewMatrix());
        setProjection(&objectShader, glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        setModel(
            &objectShader, // shader
            kirby1Pos, // translation
            glm::vec3(0.0f, 1.0f, 0.0f), // rotation axis
            220.0f, // rotation angle
            glm::vec3(0.080f) // scale
        );
        kirby.Draw(objectShader);

        // Get input
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
            kirby1Force = 3500.0f;
            kirby2Force = 10.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
            kirby1Force = 10.0f;
            kirby2Force = 35000.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
            kirby1Force = 3000.0f;
            kirby2Force = 3000.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
            kirby1Force = 10000.0f;
            kirby2Force = 10000.0f;
        }
        

        // Draw the second kirby
        setModel(
            &objectShader, // shader
            kirby2Pos, // translation
            glm::vec3(0.0f, 1.0f, 0.0f), // rotation axis
            220.0f, // rotation angle
            glm::vec3(0.080f) // scale
        );
        kirby.Draw(objectShader);

        // Move the kirbies positions in a circle
        kirby1Pos = glm::vec3(
            5.0f * cos((float)glfwGetTime() * 0.25f),
            0.0f,
            5.0f * sin((float)glfwGetTime() * 0.25f)
        );

        kirby2Pos = glm::vec3(
            5.0f * cos((float)glfwGetTime() * 0.25f + glm::radians(180.0f)),
            0.0f,
            5.0f * sin((float)glfwGetTime() * 0.25f + glm::radians(180.0f))
        );

        // Compute shader
        blackHoleComplexShader.use();
        blackHoleComplexShader.setVec3("first_black_hole_position", kirby1Pos);
        blackHoleComplexShader.setVec3("second_black_hole_position", kirby2Pos);
        blackHoleComplexShader.setFloat("first_g_force", kirby1Force);
        blackHoleComplexShader.setFloat("second_g_force", kirby2Force);
        blackHoleComplexShader.execute(nParticles / 64);
        particles.Draw(particleShader, *camera);

        // Draw the Skybox 
        skybox.Draw(skyboxShader, *camera);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void renderScene_Explosion(Camera* camera, GLFWwindow* window)
{
    GLuint nParticles = 1024000;

    // Shaders
    Shader skyboxShader("Shaders/skyboxShader.vert", "Shaders/skyboxShader.frag");
    Shader particleShader("Shaders/particlesShader.vert", "Shaders/particlesShader.frag", "Shaders/particlesShader.geom");
    ComputeShader explosionShader("Shaders/Compute/particle_explosion.comp");

    // Skybox
    Skybox skybox(SKYBOX_PATH);

    // Particles
    Particles particles(
        nParticles, // Number of particles
        PARTICLE_TEXTURE_PATH // Texture of the particles
    );

    processCallbacks(window, camera, &cameraPos);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Update camera speed
        camera->updateDeltaTime();

        // input
        processInput(window, camera);

        // render
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw particles
        explosionShader.use();
        explosionShader.setFloat("deltaTime", camera->deltaTime);
        explosionShader.setFloat("time", (float)glfwGetTime());
        explosionShader.execute(nParticles / 64);
        particles.Draw(particleShader, *camera);

        // Draw the Skybox 
        skybox.Draw(skyboxShader, *camera);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void renderScene_Spiral(Camera* camera, GLFWwindow* window)
{
    GLuint nParticles = 102400;

    // Shaders
    Shader skyboxShader("Shaders/skyboxShader.vert", "Shaders/skyboxShader.frag");
    Shader particleShader("Shaders/particlesShader.vert", "Shaders/particlesShader.frag", "Shaders/particlesShader.geom");
    ComputeShader spiralShader("Shaders/Compute/particle_shader_spiral.comp");

    // Skybox
    Skybox skybox(SKYBOX_PATH);

    // Particles
    Particles particles(
        nParticles, // Number of particles
        PARTICLE_TEXTURE_PATH // Texture of the particles
    );

    processCallbacks(window, camera, &cameraPos);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Update camera speed
        camera->updateDeltaTime();

        // input
        processInput(window, camera);

        // render
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw particles
        spiralShader.use();
        spiralShader.execute(nParticles / 64);
        particles.Draw(particleShader, *camera);

        // Draw the Skybox 
        skybox.Draw(skyboxShader, *camera);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}