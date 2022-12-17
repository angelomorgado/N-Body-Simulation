/*
    Utils.h:

        - Special file that stores global variables and auxiliary structs used in the main function
        - This is the file where stuff can be customized by modifying the global variables
*/

#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <iostream>


//=================================== GLOBAL VARIABLES ============================

// Screen Settings
#define SCR_WIDTH 1200
#define SCR_HEIGHT 900

// Camera
#define YAW -90.0f
#define PITCH 0.0f
#define SPEED 1.00f
#define SENSITIVITY 0.1f
#define ZOOM 60.0f

// Default texture (If the object doesn't have one)
#define DEFAULT_TEXTURE_DIR "Media/Textures"
#define DEFAULT_TEXTURE_NAME "default.jpg"

// ================================================================================

// Deltatime variables
struct Delta {
    float deltaTime; // Time between current frame and last frame
    float lastFrame; // Time of last frame
};

struct CameraPos {
    float lastX = SCR_WIDTH / 2.0f;
    float lastY = SCR_HEIGHT / 2.0f;
    bool firstMouse = true;
};

#endif
