/*
    Scene.h:

        - Responsible for creating the scene (model, view, projection) and methods to draw objects
*/

#pragma once

#ifndef SCENE_H
#define SCENE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

// Sets the Projection matrix in the shader
void setProjection(Shader* shader, float fov, float aspectRatio, float nearLimit, float farLimit);

// Sets the View matrix in the shader
void setView(Shader* shader, glm::mat4 view);

// Sets the Model matrix in the shader
void setModel(Shader* shader, glm::vec3 translation, glm::vec3 rotation, float angle, glm::vec3 scale);

#endif

