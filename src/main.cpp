#include <string>
#include <cstdlib>

#include "window.h"
#include "shader.h"
#include "renderer.h"
#include "camera.h"
#include "handle_input.h"
#include "mesh/perlin_mesh.h"
#include "mesh/perlin_plane.h"

void init();
void render_loop();
void calculate_delta_time();

Window* window;
Camera* camera;
Renderer* renderer;
Shader* shaderProgram;

float sensitivity = 0.05f;
double deltaTime = 0.0f;
double oldTimeLog = 0.0f;

float sky_blue_rgb[3] = { 0.53f, 0.8f, 0.92f };

float squareVertices[] = {
    // positions        // texture coordinates
     0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f  // top left
};
unsigned int squareIndices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

float cubeVertices[] = {
     // THE FRONT
     // positions        // texture coordinates
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top right
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // top left

     // THE BACK
     // positions        // texture coordinates
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top right
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom right
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom left
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f  // top left
};

unsigned int cubeIndices[] = {
    // COMPLETE FRONT FACE
    0, 1, 3,
    1, 2, 3,

    // COMPLETE BACK FACE
    4, 5, 7,
    5, 6, 7,

    // COMPLETE TOP FACE
    7, 3, 4,
    3, 0, 4,

    // COMPLETE BOTTOM FACE
    6, 2, 5,
    2, 1, 5,

    // LEFT FACE
    7, 6, 3,
    6, 2, 3,

    // RIGHT FACE
    0, 1, 4,
    1, 5, 4,

};

unsigned int sizeOfMesh = 10;
unsigned int frequency = 4;

double x_offset = 0.0f;
double z_offset = 0.0f;
float moveSpeed = 1.0f;
float scale = 0.4f;

float* perlinVertices;
unsigned int* perlinIndices;

int main( int argc, char** argv ) {

    if (argc == 4) {
        char *satisfy;

        sizeOfMesh = strtol(argv[0], &satisfy, 10) + 1;
        frequency = strtol(argv[1], &satisfy, 10) + 1;
        scale = strtod(argv[2], NULL);
        moveSpeed = strtod(argv[3], NULL);
    } else {
        std::cout << "Input square length of mesh: ";
        std::cin >> sizeOfMesh;
        std::cout << "Input frequency/smoothness [increases price by O(n^2)!]: ";
        std::cin >> frequency;
        std::cout << "Input drastic-ness: ";
        std::cin >> scale;
        std::cout << "Input speed of change (recommended 1-5): ";
        std::cin >> moveSpeed;
    }

	init();

	while (!glfwWindowShouldClose(window->window)) {
		glClearColor(sky_blue_rgb[0], sky_blue_rgb[1], sky_blue_rgb[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, polygon_modes[window->current_polygon_mode_index]);
        glPointSize(10.0f);
		render_loop();

		glfwSwapBuffers(window->window);
		glfwPollEvents();
	}
}

void render_loop() {
    calculate_delta_time();

    x_offset += moveSpeed * deltaTime;
    z_offset += moveSpeed * deltaTime;

    camera->moveCamera(
        handleMovement(
            window->window,
            camera->cameraFront,
            camera->globalUp,
            deltaTime
        )
    );

    PerlinPlane perlinPlane(
        camera,
        shaderProgram,
        sizeOfMesh,
        frequency,
        x_offset,
        z_offset,
        scale,
        glm::vec3(0.0f, 1.0f, 1.0f)
    );

	camera->updateCamera();
    perlinPlane.draw(camera->mvp);
}

void init() {
    calculate_delta_time();

	std::string pathToVertexShader = "./src/shaders/color.vert";
	std::string pathToFragmentShader = "./src/shaders/color.frag";
	std::string pathToImage = "./src/textures/img.png";

	window = new Window();
	shaderProgram = new Shader(pathToVertexShader, pathToFragmentShader);
	camera = new Camera(
		glm::vec3(-5.0f, 10.0f, 4.5f),
		glm::vec3((float)sizeOfMesh/2, 0.0f, (float)sizeOfMesh/2),
		glm::vec3(0.0f, 1.0f, 0.0f),
		(float)SCREEN_WIDTH / SCREEN_HEIGHT
	);

    shaderProgram = new Shader(pathToVertexShader, pathToFragmentShader);


    window->set_current_static_camera(camera);
}

void calculate_delta_time() {
    deltaTime = glfwGetTime() - oldTimeLog;
    oldTimeLog = glfwGetTime();
}