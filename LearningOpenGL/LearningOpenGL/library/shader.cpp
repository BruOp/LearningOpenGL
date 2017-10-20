#include "shader.h"

Shader::Shader() :
    _program(0)
{
}

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) :
    _program(setup(vertexPath, fragmentPath))
{
}

Shader::Shader(const std::string & vertexPath, const std::string & fragmentPath) :
    Shader(vertexPath.c_str(), fragmentPath.c_str())
{
}

Shader::~Shader()
{
    glDeleteProgram(_program);
}

void Shader::setup_fstream(std::string& shaderCode, std::ifstream& shaderFile, const std::string& filePath) {
    shaderFile.exceptions(std::ifstream::badbit);
    try {
        // Open file
        shaderFile.open(filePath);
        std::stringstream shaderStream;
        // Read file's buffer contents into stream
        shaderStream << shaderFile.rdbuf();
        // Close file handler
        shaderFile.close();
        // Convert stream into GLchar array
        shaderCode = shaderStream.str();
    }
    catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
}

void Shader::compile_shader(GLuint& shaderID, const GLchar* shaderCode, GLenum shaderType) {
    GLint success;
    shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, &shaderCode, NULL);
    glCompileShader(shaderID);
    // Print compile errors if any
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        getInfoLog("ERROR::SHADER::COMPILATION_FAILED\n", shaderID);
    };
}

GLuint Shader::create_program(GLuint vertexShader, GLuint fragmentShader)
{
    GLint success;
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    // Print linking errors if any
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        getInfoLog("ERROR::SHADER::PROGRAM::LINKING_FAILED\n", program);
    }
    return program;
}

GLuint Shader::setup(const GLchar * vertexPath, const GLchar * fragmentPath)
{
    // 1. Retrieve the vertex/fragment source code from the filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    Shader::setup_fstream(vertexCode, vShaderFile, vertexPath);
    Shader::setup_fstream(fragmentCode, vShaderFile, fragmentPath);

    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();

    // 2. Compile shaders
    GLuint vertex, fragment;
    compile_shader(vertex, vShaderCode, GL_VERTEX_SHADER);
    compile_shader(fragment, fShaderCode, GL_FRAGMENT_SHADER);

    auto program = Shader::create_program(vertex, fragment);

    // Delete the shaders as they're linked into our program now and no longer necessary.
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
}

void Shader::getInfoLog(const std::string &headerMessage, GLuint program)
{
    GLint infoLogLength = 4096;
    glGetShaderiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
    GLchar* infoLog = new GLchar[infoLogLength + 1];

    if (glIsShader(program)) {
        glGetShaderInfoLog(program, infoLogLength, NULL, infoLog);
    }
    else {
        glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);
    }
    std::cout << headerMessage << infoLog << std::endl;
    delete[] infoLog;
}

void Shader::use() const {
    glUseProgram(_program);
}

GLint Shader::getLocation(const std::string & name) const
{
    return glGetUniformLocation(_program, name.c_str());
}
