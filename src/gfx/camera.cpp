#include "camera.h"

Camera::Camera(
   glm::vec3 position,
   glm::vec3 target,
   glm::vec3 globalUp,
   float aspect_ratio,
   float FOV /*= 45.0f*/,
   float near /*= 0.1f*/,
   float far /*= 100.f*/
) {

   this->position = position;
   this->target = target;
   this->globalUp = globalUp;

   // initialize vectors
   cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

   // m denotes mat4
   m_lookAt = glm::lookAt(position, position + cameraFront, globalUp); // camera
   m_projection = glm::perspective(glm::radians(FOV), aspect_ratio, near, far);
   m_model = glm::mat4(1.0f);

   mvp = m_model * m_lookAt * m_projection;
}

void Camera::change_rotation(GLFWwindow* window, float xpos, float ypos, float mouseSensitivity) {
    // to make sure that the delta mouse coords doesn't freak out and move the camera too much
    if (isFirstFrame) {
        isFirstFrame = false;
        isSecondFrame = true;
    } else if (isSecondFrame) {
        glfwSetCursorPos(window, (float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2);
        isSecondFrame = false;
    }

    float deltaMouseX = xpos - (float)SCREEN_WIDTH/2;
    float deltaMouseY = (float)SCREEN_HEIGHT/2 - ypos;

    yaw += deltaMouseX * mouseSensitivity;
    pitch += deltaMouseY * mouseSensitivity;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = (float)cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = (float)sin(glm::radians(pitch));
    front.z = (float)sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);

    glfwSetCursorPos(window, (float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2);

}

void Camera::moveCamera(glm::vec3 move_vector) {
    if (move_vector != glm::vec3(0.0f, 0.0f, 0.0f)) {
        position -= move_vector;
        m_lookAt = glm::translate(m_lookAt, move_vector);
    }
}

void Camera::updateCamera() {
    m_lookAt = glm::lookAt(position, position + cameraFront, globalUp);

    mvp = m_projection * m_lookAt * m_model;
}