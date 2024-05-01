#include "mesh.h"

Mesh::Mesh() {
    // empty
}

// set
Mesh::Mesh(unsigned int *indices, float *vertices, GLsizei sizeOfIndices, GLsizei sizeOfVertices, glm::vec3 rgb) {
    this->meshType = MeshType::PLAIN_COLOR;
    this->texture = 0; // meaning no texture

    this->rgb = rgb;
    this->indices = indices;
    this->vertices = vertices;
    this->sizeOfIndices = sizeOfIndices;
    this->sizeOfVertices = sizeOfVertices;


}

Mesh::Mesh(unsigned int *indices, float *vertices, GLsizei sizeOfIndices, GLsizei sizeOfVertices, unsigned int texture) {
    this->meshType = MeshType::PLAIN_TEXTURE;
    this->rgb = glm::vec3(1.0f, 1.0f, 1.0f);

    this->texture = texture; // meaning only texture
    this->indices = indices;
    this->vertices = vertices;
    this->sizeOfIndices = sizeOfIndices;
    this->sizeOfVertices = sizeOfVertices;
}

Mesh::Mesh(unsigned int *indices, float *vertices, GLsizei sizeOfIndices, GLsizei sizeOfVertices, glm::vec3 rgb, unsigned int texture) {
    this->meshType = MeshType::TEXTURE_COLORED;

    this->rgb = rgb; // meaning texture and rgb
    this->texture = texture;
    this->indices = indices;
    this->vertices = vertices;
    this->sizeOfIndices = sizeOfIndices;
    this->sizeOfVertices = sizeOfVertices;
}