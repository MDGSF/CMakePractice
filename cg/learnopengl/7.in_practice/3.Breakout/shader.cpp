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
}

void Shader::setInteger(const char* name, int value, bool useShader) {
}

void Shader::setVector2f(const char* name, float x, float y, bool useShader) {
}

void Shader::setVector2f(
    const char* name,
    const glm::vec2& value,
    bool useShader) {
}

void Shader::setVector3f(
    const char* name,
    float x,
    float y,
    float z,
    bool useShader) {
}

void Shader::setVector3f(
    const char* name,
    const glm::vec3& value,
    bool useShader) {
}

void Shader::setVector4f(const char* name, float x, float y, float z, float w,
    bool useShader = false) {
}

void Shader::setVector4f(
    const char* name,
    const glm::vec4& value,
    bool useShader) {
}

void Shader::setMatrix4(
    const char* name,
    const glm::mat4& value,
    bool useShader) {
}

void Shader::checkCompileErrors(unsigned int object, std::string type) {
}

