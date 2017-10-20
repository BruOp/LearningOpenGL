#pragma once
#include <vector>

#include <GL/glew.h>

class Geometry
{
public:
    typedef std::vector<GLfloat> VertList;

    Geometry(const VertList &vertices, GLuint stride);
    virtual ~Geometry();

    void setVertexAttribute(GLuint index, GLuint size, GLuint stride, GLuint start);

    inline GLuint getVAO() const { return _VAO; };
    inline GLuint getVBO() const { return _VBO; };
    inline GLuint getSize() const { return _size; };

    void draw() const;
private:
    GLuint _VAO, _VBO;
    GLuint _size;
};

