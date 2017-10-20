#include "texture_manager.h"

// STB image loading
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using std::string;

Texture::Texture(const string &texturePath, GLuint activeTextureUnit) :
    _wrappingS(GL_REPEAT),
    _wrappingT(GL_REPEAT),
    _filterMag(GL_LINEAR),
    _filterMin(GL_LINEAR_MIPMAP_LINEAR),
    _texture(0),
    _textureUnit(activeTextureUnit)
{
    load_image(texturePath);
}

void Texture::setWrapping(GLint wrappingS, GLint wrappingT)
{
  _wrappingS = wrappingS;
  _wrappingT = wrappingT;
}

void Texture::setFilters(GLint filterMag, GLint filterMin)
{
  _filterMag = filterMag;
  _filterMin = filterMin;
}

GLuint Texture::load_image(const string &texturePath)
{
  // Currently always loads images as RGBA...

  // Generate and bind texture
  glGenTextures(1, &_texture);
  glActiveTexture(GL_TEXTURE0 + _textureUnit);
  glBindTexture(GL_TEXTURE_2D, _texture);

  // Set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrappingS);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrappingT);
  // Set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _filterMin);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _filterMag);

  // Load the image
  int width, height, comp;
  unsigned char* image = stbi_load(texturePath.c_str(), &width, &height, &comp, STBI_rgb_alpha);
  
  // Load the image into memory
  // Note that border (the second zero below) should always be 0 (legacy shit)
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);

  // Free up the image memory and unbind the texture
  stbi_image_free(image);
  glBindTexture(GL_TEXTURE_2D, 0);

  return _texture;
}

void Texture::bindTexture() const
{
    glActiveTexture(GL_TEXTURE0 + _textureUnit);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glActiveTexture(0);
}
