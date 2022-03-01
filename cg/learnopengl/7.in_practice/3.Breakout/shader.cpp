#include "shader.h"
#include <iostream>

Shader::Shader() {
}

Shader& Shader::use() {
  glUseProgram(this->ID);
  return *this;
}

void Shader::Compile(
    const char* vertexSource,
    const char* fragmentSource,
    const char* geometrySource) {
}

void Shader::setFloat(const char* name, float value, bool useShader) {
  if (useShader) {
    this->Use();
  }
  glUniform1f(glGetUniformLocation(this->ID, name), value);
}

void Shader::setInteger(const char* name, int value, bool useShader) {
  if (useShader) {
    this->Use();
  }
}

void Shader::setVector2f(const char* name, float x, float y, bool useShader) {
  if (useShader) {
    this->Use();
  }
}

void Shader::setVector2f(
    const char* name,
    const glm::vec2& value,
    bool useShader) {
  if (useShader) {
    this->Use();
  }
}

void Shader::setVector3f(
    const char* name,
    float x,
    float y,
    float z,
    bool useShader) {
  if (useShader) {
    this->Use();
  }
}

void Shader::setVector3f(
    const char* name,
    const glm::vec3& value,
    bool useShader) {
  if (useShader) {
    this->Use();
  }
}

void Shader::setVector4f(
    const char* name,
    float x,
    float y,
    float z,
    float w,
    bool useShader) {
  if (useShader) {
    this->Use();
  }
}

void Shader::setVector4f(
    const char* name,
    const glm::vec4& value,
    bool useShader) {
  if (useShader) {
    this->Use();
  }
}

void Shader::setMatrix4(
    const char* name,
    const glm::mat4& value,
    bool useShader) {
  if (useShader) {
    this->Use();
  }
}

void Shader::checkCompileErrors(unsigned int object, std::string type) {
  int success = 0;
  char infoLog[1024] = {0};
  if (type != "PROGRAM") {
    glGetShaderiv(object, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(object, 1024, NULL, infoLog);
      std::cout << "| ERROR::SHADER: Compile-time error: Type: "
        << type << "\n"
        << infoLog << "\n"
        << " -- --------------------------------------------------- -- "
        << std::endl;
    }
  } else {
    glGetProgramiv(object, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(object, 1024, NULL, infoLog);
      std::cout << "| ERROR::SHADER: Link-time error: Type: "
        << type << "\n"
        << infoLog << "\n"
        << " -- --------------------------------------------------- -- "
        << std::endl;
    }
  }
}

