#ifndef HANDLE_INPUT_H
#define HANDLE_INPUT_H

#include "gfx.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::vec3 handleMovement(GLFWwindow* window, glm::vec3 cameraFront, glm::vec3 cameraUp, double deltaTime);

#endif
