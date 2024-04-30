#include "perlin_mesh.h"
#include "perlin.h"

#include <cstdlib>

PerlinMesh::PerlinMesh(int square_length, int frequency, float x_offset, float z_offset, float scale) {
    this->square_length = square_length;

    square_length *= frequency;

    vertices = (float*) malloc(sizeof(float) * square_length * square_length * 3);
    indices = (unsigned int*) malloc(sizeof(unsigned int)*(square_length - 1) * (square_length - 1) * 6);


    for (unsigned int i = 0; i < square_length; i++) {
        for (unsigned int j = 0; j < square_length; j++) {
            // Calculate the index for the current vertex
            unsigned int index = (i * square_length + j) * 3;

            // Assign coordinates to the vertex
            vertices[index]     = static_cast<float>(i)/(float)frequency;
            vertices[index + 1] = perlin(
                ((float)i*0.3f*scale + x_offset)/(float)frequency,
                ((float)j*0.3f*scale + z_offset)/(float)frequency
            );
            vertices[index + 2] = static_cast<float>(j)/(float)frequency;
        }
    }

    unsigned int index = 0;
    for (unsigned int i = 0; i < square_length - 1; i++) {
        for (unsigned int j = 0; j < square_length - 1; j++) {
            // Triangle 1
            indices[index++] = j + square_length * i;
            indices[index++] = j + square_length * (i + 1);
            indices[index++] = (j + 1) + square_length * i;

            // Triangle 2
            indices[index++] = (j + 1) + square_length * i;
            indices[index++] = j + square_length * (i + 1);
            indices[index++] = (j + 1) + square_length * (i + 1);
        }
    }
}

