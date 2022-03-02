#ifndef POST_PROCESSOR_H
#define POST_PROCESSOR_Ho

#include "glad/glad.h"
#include "glm/glm.hpp"

#include "texture.h"
#include "sprite_renderer.h"
#include "shader.h"

class PostProcessor {
public:
  Shader PostProcessingShader;
  Texture2D Texture;
  unsigned int Width;
  unsigned int Height;

  bool Chaos;
  bool Confuse;
  bool Shake;

  PostProcessor(Shader shader, unsigned int width, unsigned int height);
  void BeginRender();
  void EndRender();
  void Render(float time);

private:
  unsigned int MSFBO;
  unsigned int FBO;
  unsigned int RBO;
  unsigned int VAO;

  void initRenderData();
};

#endif
