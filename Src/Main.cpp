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

// ============================= Global variables ==================================
Camera camera;
CameraPos cameraPos;

// =============================== Files ===========================================
const char* cubePath = "Media/Objects/Cube_tex/cube_textured.obj";
const char* skyboxPath = "Media/Skyboxes/skybox_galaxy/";
const char* alienPath = "Media/Objects/Alien/alien.obj";

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
    ComputeShader computeShader("Shaders/Compute/basic_shader.comp");

    //================================= Models ====================================================

	// Load the model
    Skybox skybox(skyboxPath);
    Model cube(cubePath);
    Model alien(alienPath);
    alien.changeTexture("alien.png","Media/Objects/Alien");

    //================================= Particles =====================================~
    
    // Create the particles
    Particles particles(
        1000, // Number of particles
        1.0f, // Minimum mass of the particles
        100.0f, // Maximum mass of the particles
        0.1f, // Minimum radius of the particles
        1.4f, // Maximum radius of the particles
        0.0f, // Minimum speed of the particles
        0.0f, // Maximum speed of the particles
        4.0f, // Minimum size of the particles
        10.1f // Maximum size of the particles
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
        particles.Draw(particleShader, camera);
		
        // Draw the Skybox 
        // skybox.Draw(skyboxShader, camera);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}