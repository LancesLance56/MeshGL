#ifndef VAO_H
#define VAO_H

#include "gfx.h"
#include "abo.h"

#include <iostream>
#include <cstdlib>

struct VAO {
   GLuint ID;
};

struct VAO vao_create();
void vao_destroy(struct VAO self);
void vao_bind(struct VAO self);
void vao_vattribptr(GLuint index, GLint size, GLenum type, GLsizei stride, std::size_t offset);

#endif
