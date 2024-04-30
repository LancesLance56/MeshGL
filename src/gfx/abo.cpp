#include "abo.h"

struct ABO abo_create(GLenum type, GLenum setting) {
   GLuint id;
   glGenBuffers(1, &id);

   struct ABO abo = {
      .ID = id,
      .type = type,
      .setting = setting,
   };

   return abo;
}

void abo_destroy(struct ABO self) {
   glDeleteBuffers(1, &self.ID);
}

void abo_bind(struct ABO self) {
   glBindBuffer(self.type, self.ID);
}

void abo_data(struct ABO self, GLsizeiptr size, void* data) {
   abo_bind(self);
   glBufferData(self.type, size, data, self.setting);
}

