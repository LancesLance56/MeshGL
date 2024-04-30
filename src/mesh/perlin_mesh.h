#ifndef DONUT_PERLIN_MESH_H
#define DONUT_PERLIN_MESH_H

#include <glm/glm.hpp>

class PerlinMesh {

public:
    int square_length;
    float* vertices;
    unsigned int* indices;

    explicit PerlinMesh(int square_length, int frequency, float x_offset, float z_offset, float scale);

};


#endif //DONUT_PERLIN_MESH_H
