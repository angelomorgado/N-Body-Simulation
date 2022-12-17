#include "Scene.h"

void setProjection(Shader* shader, float fov, float aspectRatio, float nearLimit, float farLimit) {
    glm::mat4 projection = glm::perspective(fov, aspectRatio, nearLimit, farLimit);
    shader->setMat4("projection", projection);
}

void setView(Shader* shader, glm::mat4 view) {
    shader->setMat4("view", view);
}

void setModel(Shader* shader, glm::vec3 translation, glm::vec3 rotation, float angle, glm::vec3 scale) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, translation);
    model = glm::rotate(model, glm::radians(angle), rotation);
    model = glm::scale(model, scale);
    shader->setMat4("model", model);
}