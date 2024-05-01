#ifndef PERLIN_PLANE_H
#define PERLIN_PLANE_H

#include "gfx.h"
#include "mesh.h"
#include "renderer.h"
#include "camera.h"

class PerlinPlane {
    Renderer *renderer;
    Shader *shader;
    Mesh *mesh;

public:
    PerlinPlane(
        Camera *camera,
        Shader *shader,
        unsigned int square_length,
        unsigned int frequency,
        float x_offset,
        float z_offset,
        float scale,
        glm::vec3 rgb
    );

    void draw(glm::mat4 mvp);
};


#endif //PERLIN_PLANE_H
