#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <map>

#include "glad/glad.h"
#include "glm/glm.hpp"

#include "texture.h"
#include "shader.h"

struct Character {
  unsigned int TextureID;
  glm::ivec2 Size;
  glm::ivec2 Bearing;
  unsigned int Advance;
};

class TextRenderer {
public:
  // holds a list of pre-compiled Characters
  std::map<char, Character> Characters;

  // shader used for text rendering
  Shader TextShader;

  TextRenderer(unsigned int width, unsigned int height);

  // pre-compiles a list of characters from the given font
  void Load(std::string font, unsigned int fontSize);

  // renders a string of text using the precompiled list of characters
  void RenderText(
      std::string text,
      float x,
      float y,
      float scale,
      glm::vec3 color = glm::vec3(1.0f));

private:
  unsigned int VAO;
  unsigned int VBO;
};

#endif
