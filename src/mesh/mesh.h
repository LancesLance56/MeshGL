#ifndef MESH_H
#define MESH_H

#include "gfx.h"
#include <glm/glm.hpp>

enum class MeshType {
    PLAIN_COLOR,
    PLAIN_TEXTURE,
    TEXTURE_COLORED
};

class Mesh {
    unsigned int* indices;
    float* vertices;
    GLsizei sizeOfIndices;
    GLsizei sizeOfVertices;

    // optional
    glm::vec3 rgb;
    unsigned int texture;

    // type identifier
    MeshType meshType;

    Mesh();

    Mesh(
        unsigned int* indices,
        float* vertices,
        GLsizei sizeOfIndices,
        GLsizei sizeOfVertices,
        unsigned int texture
    );
    Mesh(
        unsigned int* indices,
        float* vertices,
        GLsizei sizeOfIndices,
        GLsizei sizeOfVertices,
        glm::vec3 rgb,
        unsigned int texture
    );

public:
    Mesh(
        unsigned int* indices,
        float* vertices,
        GLsizei sizeOfIndices,
        GLsizei sizeOfVertices,
        glm::vec3 rgb
    );
};

#endif //MESH_H
