#ifndef RENDERER_H
#define RENDERER_H

#include "vao.h"
#include "abo.h"
#include "shader.h"

#include "texture.h"
#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class Renderer {
   struct VAO vao;
   struct ABO vbo;
   struct ABO ebo;

   bool shouldDrawElements = false; // glDrawArrays or glDrawElements

   GLuint UNDEFINED_TEXTURE_LOCATION = 180;
   GLuint count;
   GLuint texture = UNDEFINED_TEXTURE_LOCATION;


public:
   glm::mat4 m_model;
   glm::mat4 mvp;
   Shader* shader;

   Renderer();
   Renderer(Shader* shader, float vertices[], unsigned int indices[], GLsizei sizeOfVertices, GLsizei sizeOfIndices, glm::mat4 mvp, const char* mvp_name);
   // monster constructor go brrr
   Renderer(Shader* shader, const std::string& pathToImage, float vertices[], unsigned int indices[], GLsizei sizeOfVertices, GLsizei sizeOfIndices, glm::mat4 mvp, const char* mvp_name);
   void Draw();
   void SetPolygonMode(GLenum mode);
   void SetMVP(glm::mat4 mvp);

};

#endif
