#include <shader/shader.hpp>

#include <string>
#include <iostream>

#include <utilities/utilities.hpp>
#include <utilities/colour_output.hpp>

Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath) {
    // Read files and store the contents.
    // Note: each pair of lines can't be combined, e.g., ReadFile(vertexFilePath).c_str(),
    // as the string goes out of scope after the function returns.
    std::string vertexCode = ReadFile(vertexFilePath);
    const char* vertexSource = vertexCode.c_str();
    std::string fragmentCode = ReadFile(fragmentFilePath);
	const char* fragmentSource = fragmentCode.c_str();

    // Variables for error checking
    int success;
    char infoLog[512];

    // Create vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Check vertex shader compilation
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << FG_RED << "OpenGL Error: " << FG_YELLOW << "SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << FG_DEFAULT << std::endl;
    }

    // Create fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Check fragment shader compilation
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << FG_RED << "OpenGL Error: " << FG_YELLOW << "SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << FG_DEFAULT << std::endl;
    }

    // Create shader program
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    // Check shader program compilation and linking
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        std::cout << FG_RED << "OpenGL Error: " << FG_YELLOW << "SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << FG_DEFAULT << std::endl;
    }

    // Delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Do a final check to see if everything went well
    glCheckError();
}

void Shader::Activate() {
    glUseProgram(programID);
}

void Shader::Delete() {
    glDeleteProgram(programID);
}