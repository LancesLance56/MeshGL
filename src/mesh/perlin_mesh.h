#ifndef PERLIN_MESH_H
#define PERLIN_MESH_H

#include <glm/glm.hpp>

class PerlinMesh {

public:
    int square_length;
    float* vertices;
    unsigned int* indices;

    explicit PerlinMesh(int square_length, int frequency, float x_offset, float z_offset, float scale);

};


#endif // PERLIN_MESH_H
