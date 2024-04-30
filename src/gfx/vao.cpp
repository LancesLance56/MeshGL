#include "vao.h"

GLenum catch_error;

struct VAO vao_create() {
   GLuint id;
   glGenVertexArrays(1, &id);
   struct VAO self = {
      .ID = id
   };
   return self;
}

void vao_destroy(struct VAO self) {
   glDeleteVertexArrays(1, &self.ID);
}

void vao_bind(struct VAO self) {
   glBindVertexArray(self.ID);
}

void vao_vattribptr(GLuint index, GLint size, GLenum type, GLsizei stride, std::size_t offset) {
   glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)offset);
   glEnableVertexAttribArray(index);
}

