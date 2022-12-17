/*
    Config.h:

        - File responsible for initializing every tool and processing events that happen throughout the life cycle
*/

#pragma once

#ifndef CONFIG_H
#define CONFIG_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <Camera.h>
#include <Utils.h>

//void processInput(GLFWwindow* window, Camera* camera);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void glfw_setup();
void window_setup(GLFWwindow* window);
void glad_setup();
void printGPUinfo();

#endif