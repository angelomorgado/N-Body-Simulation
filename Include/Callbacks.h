/*
    Callbacks.h:

        - Deals with everything related to callbacks such as mouse position and mouse scroll events
        - The main function processCallbacks is responsible for dealing with all callbacks associated
          with the program
        note: Can't make a .cpp file due to the callbacks not allowing that
*/

#pragma once

#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <Camera.h>
#include <Utils.h>
#include <Skybox.h>
#include <GLFW/glfw3.h>
#include <iostream>

Camera* cam;
CameraPos* camPos;
Skybox* skybox;
bool* is_filtered;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    cam->ProcessMouseScroll(static_cast<float>(yoffset));
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (camPos->firstMouse)
    {
        camPos->lastX = xpos;
        camPos->lastY = ypos;
        camPos->firstMouse = false;
    }

    float xoffset = xpos - camPos->lastX;
    float yoffset = camPos->lastY - ypos; // reversed since y-coordinates go from bottom to top

    camPos->lastX = xpos;
    camPos->lastY = ypos;

    cam->ProcessMouseMovement(xoffset, yoffset);
}

// This callback function can't be used for things like movement because it doesn't work while pressing
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Leave the program
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

	// Keybinds
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
	{
		*is_filtered = !*is_filtered;
		std::cout << "Filter: " << *is_filtered << std::endl;
	}
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window, Camera* camera)
{
    // Exit program
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Camera movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, camera->deltaTime);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, camera->deltaTime);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, camera->deltaTime);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, camera->deltaTime);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera->ProcessKeyboard(UP, camera->deltaTime);

    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        camera->ProcessKeyboard(DOWN, camera->deltaTime);

}

void processCallbacks(GLFWwindow* window, Camera* camera, CameraPos* cameraPos, bool* isFiltered){
    cam = camera;
    camPos = cameraPos;
    is_filtered = isFiltered;

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
}

#endif