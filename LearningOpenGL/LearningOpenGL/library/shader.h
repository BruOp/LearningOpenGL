#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

class Shader {
public:
    // Constructor reads and builds the shader
    Shader();
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    Shader(const std::string & vertexPath, const std::string & fragmentPath);
    ~Shader();

    // Use the program
    void use() const;

    GLint getLocation(const std::string &name) const;
    inline GLuint getProgram() const { return _program; };
private:
    // The program ID
    GLuint _program;

    void getInfoLog(const std::string &headerMessage, GLuint program);
    void setup_fstream(std::string& shaderCode, std::ifstream& shaderFile, const std::string& filePath);
    void compile_shader(GLuint & shaderID, const GLchar * shaderCode, GLenum shaderType);
    GLuint create_program(GLuint, GLuint);
    GLuint setup(const GLchar* vertexPath, const GLchar* fragmentPath);
};
