#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class Texture2D {
public:
  unsigned int ID; // holds the ID of the texture object
  unsigned int Width;
  unsigned int Height;
  unsigned int InternalFormat;
  unsigned int ImageFormat;
  unsigned int WrapS;
  unsigned int WrapT;
  unsigned int FilterMin;
  unsigned int FilterMax;

  Texture2D();

  // generates texture from image data
  void Generate(unsigned int width, unsigned int height, unsigned char* data);

  // binds the texture as the current active GL_TEXTURE_2D texture object
  void Bind() const;
};

#endif
