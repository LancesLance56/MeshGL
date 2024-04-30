#include "renderer.h"

Renderer::Renderer() { };

// no texture
Renderer::Renderer(Shader* shader, float vertices[], unsigned int indices[], GLsizei sizeOfVertices, GLsizei sizeOfIndices, glm::mat4 mvp, const char* mvp_name) {
    this->count = sizeOfIndices/sizeof(unsigned int);
    this->shader = shader;
    this->mvp = mvp;

    shouldDrawElements = true;
    count = sizeOfIndices/sizeof(unsigned int);

    m_model = glm::mat4(1.0f);

    vao = vao_create();
    vbo = abo_create(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    ebo = abo_create(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

    vao_bind(vao);

    abo_data(vbo, sizeOfVertices, vertices);
    abo_data(ebo, sizeOfIndices, indices);

    glUseProgram(shader->ID);

    glUniformMatrix4fv(glGetUniformLocation(shader->ID, mvp_name), 1, GL_FALSE, &mvp[0][0]);

    vao_vattribptr(0, 3, GL_FLOAT, 3 * sizeof(float), 0);
}

Renderer::Renderer(Shader* shader, const std::string& pathToImage, float vertices[], unsigned int indices[], GLsizei sizeOfVertices, GLsizei sizeOfIndices, glm::mat4 mvp, const char* mvp_name) {
   shouldDrawElements = true;
   this->count = sizeOfIndices/sizeof(unsigned int);
   this->shader = shader;
   this->mvp = mvp;

   m_model = glm::mat4(1.0f);

   vao = vao_create();
   vbo = abo_create(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
   ebo = abo_create(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

   vao_bind(vao);

   abo_data(vbo, sizeOfVertices, vertices);
   abo_data(ebo, sizeOfIndices, indices);

   vao_vattribptr(0, 3, GL_FLOAT, 5 * sizeof(float), 0);
   vao_vattribptr(1, 2, GL_FLOAT, 5 * sizeof(float), 3*sizeof(float));

   glUseProgram(shader->ID);

   glUniformMatrix4fv(glGetUniformLocation(shader->ID, mvp_name), 1, GL_FALSE, &mvp[0][0]);

   texture = create_opengl_texture(pathToImage, shader->ID);
   if (texture == 0) {
      std::cout << "create_opengl_texture failed" << std::endl;
   }
}

void Renderer::SetMVP(glm::mat4 mvp) {
    this->mvp = mvp;
}

void Renderer::Draw() {
   glUniformMatrix4fv(glGetUniformLocation(shader->ID, "mvp"), 1, GL_FALSE, &mvp[0][0]);

   if (texture == UNDEFINED_TEXTURE_LOCATION) {
      glUseProgram(shader->ID);
      vao_bind(vao);
      glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
   } else {
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, texture);

      glUseProgram(shader->ID);
      vao_bind(vao);
      glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
   }
}

void Renderer::SetPolygonMode(GLenum mode) {
   if (mode != GL_FILL || mode != GL_LINE || mode != GL_POINT) {
      std::cerr << "Selected mode is not a valid drawing mode!" << std::endl;
      return;
   }

   glPolygonMode(GL_FRONT, mode);
}


