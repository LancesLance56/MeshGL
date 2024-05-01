#include <iostream>
#include "window.h"

void cursor_position_callback(GLFWwindow* window, double x, double y);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void changePolygonMode();

unsigned int* current_polygon_mode_index_ptr;

Camera* currentStaticCamera;

Window::Window() {
    current_polygon_mode_index_ptr = &current_polygon_mode_index;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Donut.cpp", NULL, NULL);
    if (window == nullptr) {
      std::cerr << "Failed to create a GLFW window!" << std::endl;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cerr << "Failed to initialize GLAD!" << std::endl;
    }

    // glEnable(...)
    glEnable(GL_DEPTH_TEST);
}

void Window::set_current_static_camera(Camera* camera) {
    currentStaticCamera = camera;
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    if (currentStaticCamera == nullptr) {
        std::cout << "Didn't connect a camera to the window" << std::endl;
        return;
    }

    currentStaticCamera->change_rotation(window, xpos, ypos, 0.1f);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
   glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, true);
                break;
            case GLFW_KEY_M:
                changePolygonMode();
                break;
            default:
                break;
        }

    }
}

void changePolygonMode() {
   if ((*current_polygon_mode_index_ptr) == 2) {
      (*current_polygon_mode_index_ptr) = 0;
   } else {
      (*current_polygon_mode_index_ptr)++;
   }
}