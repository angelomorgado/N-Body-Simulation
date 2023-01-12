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
#include <iostream>
#include <thread>

#include "Configuration.h"
#include "Camera.h"
#include "Scenes.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main()
{
    //=================================== Setup ==============================================
    glfw_setup();
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "N-Body Simulation", NULL, NULL);
    window_setup(window);
    glad_setup();
	printGPUinfo();

    Camera camera = Camera(
        glm::vec3(-1.99221f, 1.42674f, 5.2215f), // Camera initial position (world position),
		glm::vec3(7.0f, 2.0f, 0.0f) // Camera initial target (world position)
    );

    // Available scenes
    enum scenes{
        physics = 1,
        black_hole_simple = 2,
        black_hole_complex = 3,
        big_bang = 4,
        spiral = 5,
        point_cloud = 6
    };

    GLuint activeScene = point_cloud;

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
            renderScene_ComplexBlackHole(&camera, window);
            break;
        case big_bang:
            renderScene_Explosion(&camera, window);
            break;
        case spiral:
            renderScene_Spiral(&camera, window);
            break;
        case point_cloud:
            renderScene_PointCloud(&camera, window);
            break;
        default:
            break;
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}