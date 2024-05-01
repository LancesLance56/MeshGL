#include "perlin_plane.h"
#include "perlin_mesh.h"

PerlinPlane::PerlinPlane(Camera *camera, Shader *shader, unsigned int square_length, unsigned int frequency, float x_offset, float z_offset, float scale, glm::vec3 rgb) {
    unsigned int updatedSizeOfMesh = square_length*frequency;

    glUniform3fv(glGetUniformLocation(shader->ID, "color"), 1, glm::value_ptr(rgb));

    PerlinMesh perlinMesh(square_length, frequency, x_offset, z_offset, scale);
    mesh = new Mesh(
        perlinMesh.indices,
        perlinMesh.vertices,
        (updatedSizeOfMesh-1)*(updatedSizeOfMesh-1)*6*sizeof(unsigned int),
        updatedSizeOfMesh*updatedSizeOfMesh*3*sizeof(float),
        rgb
    );

    renderer = new Renderer(
        shader,
        perlinMesh.vertices,
        perlinMesh.indices,
        updatedSizeOfMesh*updatedSizeOfMesh*3*sizeof(float), // NOLINT(*-narrowing-conversions)
        (updatedSizeOfMesh-1)*(updatedSizeOfMesh-1)*6*sizeof(unsigned int), // NOLINT(*-narrowing-conversions)
        camera->mvp,
        "mvp"
    );
}

void PerlinPlane::draw(glm::mat4 mvp) {
    renderer->draw();
    renderer->set_mvp(mvp);
}