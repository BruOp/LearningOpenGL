#pragma once
#include "Geometry.h"

Geometry::Geometry(const VertList &vertices, GLuint stride) :
    _size(vertices.size() / stride),
    _VAO(0),
    _VBO(0)
{
    // 1. Initialize buffer and vertex array
    glGenBuffers(1, &_VBO);
    glGenVertexArrays(1, &_VAO);

    // 2. Bind Vertex Array Object
    glBindVertexArray(_VAO);

    // 3. Bind Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);

    // 4. Copy our vertex data into the currently bound buffer
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices.front()), &vertices.front(), GL_STATIC_DRAW);
    
    // 5. Set our vertex attribute pointers
    setVertexAttribute(0, 3, 8, 0);
    setVertexAttribute(1, 3, 8, 3);
    setVertexAttribute(2, 2, 8, 6);

    glBindVertexArray(0);
}

Geometry::~Geometry()
{
}

void Geometry::setVertexAttribute(GLuint index, GLuint size, GLuint stride, GLuint start) {
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(start * sizeof(GLfloat)));
    glEnableVertexAttribArray(index);
}

void Geometry::draw() const {
    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES, 0, _size);
    glBindVertexArray(0);
}