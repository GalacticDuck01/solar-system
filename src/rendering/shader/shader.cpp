#include <rendering/shader/shader.hpp>

#include <string>
#include <iostream>

#include <glad/glad.h>
#include <utilities/utilities.hpp>

Shader::Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
    : shaderProgram(0), vertexShader(0), fragmentShader(0) {

    // Create a shader object and compile it during runtime
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderSource = readFile(vertexShaderFile);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check for compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error: Vertex shader compilation failed\n" << infoLog << std::endl;
    }

    // Perform the same steps for the fragment shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSource = readFile(fragmentShaderFile);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check for compilation errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Error: Fragment shader compilation failed\n" << infoLog << std::endl;
    }

    // Create a shader program and link the two shader steps together
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Make sure to cleanup the individual shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(shaderProgram);
}

void Shader::Use() {
    glUseProgram(shaderProgram);
}