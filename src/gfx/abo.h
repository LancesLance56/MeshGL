#ifndef ABO_H
#define ABO_H

#include "gfx.h"

// buffer object
struct ABO {
   GLuint ID;
   GLenum type; // e.g. GL_ELEMENT_ARRAY_BUFFER
   GLenum setting; // e.g. GL_DYNAMIC_DRAW
};

struct ABO abo_create(GLenum type, GLenum setting);
void abo_destroy(struct ABO self);
void abo_bind(struct ABO self);
void abo_data(struct ABO self, GLsizeiptr size, void* data);


#endif
