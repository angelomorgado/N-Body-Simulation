/**
 * @file Main.cpp
 * @author Ângelo Morgado, Henrique Jesus, Manuel Magalhães
 * @brief The main file of the project where the project is initialized and the main loop is executed.
 * @version 1
 * @date 2022-12-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Configuration.h"
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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <thread>

void renderScene_Physics(Camera* camera, GLFWwindow* window);
void renderScene_SimpleBlackHole(Camera* camera, GLFWwindow* window);
void renderScene_ComplexBlackHole(Camera* camera, GLFWwindow* window);
void renderScene_Explosion(Camera* camera, GLFWwindow* window);
void renderScene_Spiral(Camera* camera, GLFWwindow* window);


// =============================== Global Variables =======================================
#define PARTICLE_TEXTURE_PATH "Media/Textures/star.png" // Texture of the particles
#define SKYBOX_PATH "Media/Skyboxes/skybox_galaxy/" // Texture to the skybox
Camera camera;
CameraPos cameraPos;

int main()
{
    //=================================== Setup ==============================================
    glfw_setup();
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "N-Body Simulation", NULL, NULL);
    window_setup(window);
    glad_setup();
	printGPUinfo();

    camera = Camera(
        glm::vec3(-1.99221f, 1.42674f, 5.2215f), // Camera initial position (world position),
		glm::vec3(7.0f, 2.0f, 0.0f) // Camera initial target (world position)
    );

    // Change scene
    enum scenes{
        physics = 1,
        black_hole_simple = 2,
        black_hole_complex = 3,
        big_bang = 4,
        spiral = 5,
        point_cloud = 6
    };

    GLuint activeScene = big_bang;

    //=================================== Scenes ==============================================
    switch (activeScene)
    {
        case physics:
            renderScene_Physics(&camera, window);
            break;
        case black_hole_simple:
            renderScene_SimpleBlackHole(&camera, window);
            break;
        case black_hole_complex:
            std::cout << "Entered!" << std::endl;
            renderScene_ComplexBlackHole(&camera, window);
            break;
        case big_bang:
            renderScene_Explosion(&camera, window);
            break;
        case spiral:
            renderScene_Spiral(&camera, window);
            break;
        case point_cloud:
            break;
        default:
            break;
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}


// =================================== Scenes ===============================================
void renderScene_Physics(Camera* camera, GLFWwindow* window)
{
    GLuint nParticles = 10240;

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

        // Draw particles
        physicsShader.use();
        physicsShader.setFloat("deltaTime", camera->deltaTime);
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
    Shader skyboxShader("Shaders/skyboxShader.vert", "Shaders/skyboxShader.frag");
    Shader particleShader("Shaders/particlesShader.vert", "Shaders/particlesShader.frag", "Shaders/particlesShader.geom");
    ComputeShader blackHoleSimpleShader("Shaders/Compute/particle_shader_black_hole.comp");

    // Skybox
    Skybox skybox(SKYBOX_PATH);

    // Particles
    Particles particles(
        nParticles, // Number of particles
        PARTICLE_TEXTURE_PATH // Texture of the particles
    );

    // Variables
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
    Model kirby("Media/Objects/Kirby.fbx");

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
    glm::vec3 kirby1Pos = glm::vec3(-5.0f,0.0f,0.0f);
    float kirby1Force = 1000.0f;
    glm::vec3 kirby2Pos = glm::vec3(5.0f,0.0f,0.0f);
    float kirby2Force = 1000.0f;

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
            0.0f, // rotation angle
            glm::vec3(0.015f) // scale
        );
        kirby.Draw(objectShader);

        // Draw the second kirby
        setModel(
            &objectShader, // shader
            kirby2Pos, // translation
            glm::vec3(0.0f, 1.0f, 0.0f), // rotation axis
            0.0f, // rotation angle
            glm::vec3(0.015f) // scale
        );
        kirby.Draw(objectShader);

        // Move the kirbies positions in a circle
        kirby1Pos = glm::vec3(
            5.0f * cos((float)glfwGetTime() * 0.5f),
            0.0f,
            5.0f * sin((float)glfwGetTime() * 0.5f)
        );

        kirby2Pos = glm::vec3(
            5.0f * cos((float)glfwGetTime() * 0.5f + glm::radians(180.0f)),
            0.0f,
            5.0f * sin((float)glfwGetTime() * 0.5f + glm::radians(180.0f))
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
    GLuint nParticles = 10240;

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
    GLuint nParticles = 10240;

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