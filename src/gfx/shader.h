#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "gfx.h"

enum class ShaderType {
   VERTEX_SHADER,
   FRAGMENT_SHADER,
   SHADER_PROGRAM
};


class Shader {

public:
   GLuint ID;

   Shader();
   Shader(std::string pathToVertexShader, std::string pathToFragmentShader);
   void checkShaderCompilerErrors(GLuint shaderID, ShaderType shaderType);

};

#endif


