#include "shader.h"

Shader::Shader() {
   
}

Shader::Shader(std::string pathToVertexShader, std::string pathToFragmentShader) {
   // get code
   std::string vertexCode;
   std::string fragmentCode;
   std::ifstream vShaderFile;
   std::ifstream fShaderFile;
   // ensure ifstream objects can throw exceptions:
   vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
   fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
   try {
      // open files
      vShaderFile.open(pathToVertexShader);
      fShaderFile.open(pathToFragmentShader);
      std::stringstream vShaderStream, fShaderStream;
      // read file's buffer contents into streams
      vShaderStream << vShaderFile.rdbuf();
      fShaderStream << fShaderFile.rdbuf();
      // close file handlers
      vShaderFile.close();
      fShaderFile.close();
      // convert stream into string
      vertexCode   = vShaderStream.str();
      fragmentCode = fShaderStream.str();
   }

   catch (std::ifstream::failure& e) {
      std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
   }

   const char* vShaderCode = vertexCode.c_str();
   const char* fShaderCode = fragmentCode.c_str();

   // make the shaderProgram
   unsigned int vertexShader, fragmentShader;
   vertexShader = glCreateShader(GL_VERTEX_SHADER);
   fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(vertexShader, 1, &vShaderCode, NULL);
   glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
   glCompileShader(vertexShader);
   glCompileShader(fragmentShader);

    check_shader_compiler_errors(vertexShader, ShaderType::VERTEX_SHADER);
    check_shader_compiler_errors(fragmentShader, ShaderType::FRAGMENT_SHADER);

   ID = glCreateProgram();
   glAttachShader(ID, vertexShader);
   glAttachShader(ID, fragmentShader);
   glLinkProgram(ID);

    check_shader_compiler_errors(ID, ShaderType::SHADER_PROGRAM);

   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);


}

void Shader::check_shader_compiler_errors(GLuint shaderID, ShaderType shaderType) {
   int success1;
   int success2;
   char infoLog[512];
   glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success1);
   glGetProgramiv(shaderID, GL_LINK_STATUS, &success2);   

   switch (shaderType) {
      case ShaderType::VERTEX_SHADER:
         if (success1) { return; }
         glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
         std::cerr << "Error: Vertex Shader Compilation Failed\n" << infoLog << std::endl;
         break;
      case ShaderType::FRAGMENT_SHADER:
         if (success1) { return; }
         glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
         std::cerr << "Error: Fragment Shader Compilation Failed\n" << infoLog << std::endl;
         break;
      case ShaderType::SHADER_PROGRAM:
         if (!success2) {
            glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
            std::cerr << "Error: Shader Program Compilation Failed\n" << infoLog << std::endl;
            break;
         }
   }
}

