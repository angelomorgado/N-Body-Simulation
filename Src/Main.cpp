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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <thread>

// ============================= Global variables ==================================
Camera camera;
CameraPos cameraPos;

// =============================== Files ===========================================
const char* cubePath = "Media/Objects/Pyramid/pyramid.obj";
const char* skullPath = "Media/Objects/Skull/Skull.obj";
const char* alienPath = "Media/Objects/Alien/alien.obj";
const char* planePath = "Media/Objects/Plane/plane.obj";
const char* skyboxPath = "Media/Skyboxes/skybox_galaxy/";

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
	// Shader skyboxShader("Shaders/skyboxShader.vert", "Shaders/skyboxShader.frag");
	
    Shader screenShader("Shaders/Screen/simpleScreen.vert", "Shaders/Screen/simpleScreen.frag");

    ComputeShader computeShader("Shaders/Compute/basic_shader.comp");

    //================================= Models ====================================================

	// Load the model
    // Skybox skybox(skyboxPath);
    // Model cube(cubePath);
	// cube.changeTexture("random.jpg","Media/Textures");

    // =============================== Framebuffer ===================================
    Framebuffer framebuffer;

    //================================= Particles =====================================~
    
	
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

    // draw as wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
    // =================================== Main loop ===============================================
    while (!glfwWindowShouldClose(window))
    {
        // Update camera speed
        camera.updateDeltaTime();

        // input
        processInput(window, &camera);

        // FRAMEBUFFER - Bind to framebuffer and draw scene
        framebuffer.bind();

        // render
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw an object  
        // objectShader.use();
		// setView(&objectShader, camera.GetViewMatrix());
		// setProjection(&objectShader, glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // setModel(
        //     &objectShader, // shader
        //     glm::vec3(0.0f,0.5f,0.0f), // translation
		// 	glm::vec3(0.0f, 1.0f, 0.0f), // rotation axis
        //     0.0f,//(float)glfwGetTime() * 2.5f, // rotation angle
        //     glm::vec3(1.0f) // scale
        //     );
        // cube.Draw(objectShader);
		
        // Draw the Skybox 
        // skybox.Draw(skyboxShader, camera);

		// Unbind the framebuffer and draw the quad
        framebuffer.unbind();
        framebuffer.drawQuad(screenShader);
		
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}