#pragma once

#include <string>
#include <GL/glew.h>
#include "shader.h"

class Texture
{
public:
    Texture(const std::string &texturePath, GLuint activeTextureUnit);

    void setWrapping(GLint wrappingS, GLint wrappingT);
    void setFilters(GLint filterMag, GLint filterMin);
    GLuint load_image(const std::string &texturePath);

    void bindTexture() const;

    inline GLuint getTexture() const { return _texture; };
    inline GLuint getTextureUnit() const { return _textureUnit; };

private:

    GLuint _texture;
    
    GLint _wrappingS;
    GLint _wrappingT;
    GLint _filterMag;
    GLint _filterMin;
    
    GLuint _textureUnit;
};