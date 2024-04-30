#include "handle_input.h"

glm::vec3 handleMovement(GLFWwindow* window, glm::vec3 cameraFront, glm::vec3 cameraUp, double deltaTime) {
    glm::vec3 moveToNormalized(0.0f, 0.0f, 0.0f);

    const float cameraSpeed = 1.2f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        moveToNormalized -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        moveToNormalized += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        moveToNormalized += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        moveToNormalized -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        moveToNormalized += cameraUp*cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        moveToNormalized -= cameraUp*cameraSpeed;

    if (moveToNormalized != glm::vec3(0.0f, 0.0f, 0.0f)) {
        moveToNormalized = glm::normalize(moveToNormalized);
        moveToNormalized *= deltaTime;
    }

    return moveToNormalized;
}
