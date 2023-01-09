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

void checkForErrors()
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::cout << "OpenGL error: " << err << std::endl;
    }
}

Camera camera;
CameraPos cameraPos;

// =============================== Global Variables =======================================
#define N_PARTICLES 102400 // Number of particles
#define PARTICLE_TEXTURE_PATH "Media/Textures/star.png" // Texture of the particles
#define SKYBOX_PATH "Media/Skyboxes/skybox_galaxy/" // Texture to the skybox

int main()
{
    //=================================== Setup ==============================================
    glfw_setup();
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "N-Body Simulation", NULL, NULL);
    window_setup(window);
    glad_setup();
	printGPUinfo();

    //=================================== Shaders ==============================================
    //Shader based on the file
    Shader objectShader("Shaders/targetShader.vert", "Shaders/targetShader.frag");
	Shader skyboxShader("Shaders/skyboxShader.vert", "Shaders/skyboxShader.frag");
    Shader particleShader("Shaders/particlesShader.vert", "Shaders/particlesShader.frag", "Shaders/particlesShader.geom");
    ComputeShader computeShader("Shaders/Compute/particle_shader_black_hole.comp");

    //================================= Models ====================================================
	// Load the model
    Skybox skybox(SKYBOX_PATH);
    Model kirby("Media/Objects/Kirby.fbx");

    //================================= Particles =====================================
    
    // Create the particles
    Particles particles(
        N_PARTICLES, // Number of particles
        PARTICLE_TEXTURE_PATH // Texture of the particles
    );
	
	//================================ Light ========================================
    // Default Light
    objectShader.use();
    objectShader.setVec3("objectColor", 1.0f, 1.0f, 1.0f);
    objectShader.setVec3("light.position", 1.0f, 5.0f, 1.0f);
    objectShader.setVec3("light.ambient", 0.6f, 0.6f, 0.6f);
    objectShader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
    objectShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

    // Default Material
    Material default_mat;
    default_mat.Ambient   = glm::vec3(1.0f);
    default_mat.Diffuse   = glm::vec3(0.6f);
    default_mat.Specular  = glm::vec3(0.6f);
    default_mat.Shininess = 0.6f;

    //================================= Scenes variables =====================================
    glm::vec3 kirby1Pos = glm::vec3(-5.0f,0.0f,0.0f);
    float kirby1Force = 1000.0f;
    glm::vec3 kirby2Pos = glm::vec3(5.0f,0.0f,0.0f);
    float kirby2Force = 1000.0f;

    // ====================================== Scene Setup ===============================================
    camera = Camera(
        glm::vec3(-1.99221f, 1.42674f, 5.2215f), // Camera initial position (world position),
		glm::vec3(7.0f, 2.0f, 0.0f) // Camera initial target (world position)
    );
 
    // Process all input Callbacks
	processCallbacks(window, &camera, &cameraPos);
	
    // =================================== Main loop ===============================================
    while (!glfwWindowShouldClose(window))
    {
        // Update camera speed
        camera.updateDeltaTime();

        // input
        processInput(window, &camera);

        // render
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw the particles
        computeShader.use();
        computeShader.setFloat("deltaTime", camera.deltaTime);
        computeShader.setFloat("deltaTime", camera.deltaTime);
        computeShader.setVec3("first_black_hole_position", kirby1Pos);
        computeShader.setVec3("second_black_hole_position", kirby2Pos);
        computeShader.setFloat("first_g_force", kirby1Force);
        computeShader.setFloat("second_g_force", kirby2Force);
        computeShader.setFloat("time", (float)glfwGetTime());
        computeShader.execute(N_PARTICLES / 64);
        particles.Draw(particleShader, camera);

        // Draw the first kirby
        objectShader.use();
        setView(&objectShader, camera.GetViewMatrix());
        setProjection(&objectShader, glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        setModel(
            &objectShader, // shader
            kirby1Pos, // translation
            glm::vec3(0.0f, 1.0f, 0.0f), // rotation axis
            0.0f,//(float)glfwGetTime() * 2.5f, // rotation angle
            glm::vec3(0.015f) // scale
        );
        objectShader.setVec3("material.ambient", default_mat.Ambient);
        objectShader.setVec3("material.diffuse", default_mat.Diffuse);
        objectShader.setVec3("material.specular", default_mat.Specular);
        objectShader.setFloat("material.shininess", default_mat.Shininess);
        kirby.Draw(objectShader);

        // Draw the second kirby
        setModel(
            &objectShader, // shader
            kirby2Pos, // translation
            glm::vec3(0.0f, 1.0f, 0.0f), // rotation axis
            0.0f,//(float)glfwGetTime() * 2.5f, // rotation angle
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


        // Draw the Skybox 
        skybox.Draw(skyboxShader, camera);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}