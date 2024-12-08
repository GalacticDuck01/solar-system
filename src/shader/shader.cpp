#include <shader/shader.hpp>

#include <string>

#include <utilities/utilities.hpp>

Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath) {
    // 1. retrieve the vertex/fragment source code from filePath
    const char* vertexCode = ReadFile(vertexFilePath).c_str();
    const char* fragmentCode = ReadFile(fragmentFilePath).c_str();

    // 2. compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCode, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
    glCompileShader(fragmentShader);

    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate() {
    glUseProgram(programID);
}

void Shader::Delete() {
    glDeleteProgram(programID);
}