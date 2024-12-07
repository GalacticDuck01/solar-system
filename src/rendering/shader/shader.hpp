#pragma once

#include <string>

class Shader {
    public:
        Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        ~Shader();

        void Use();

    private:
        unsigned int shaderProgram;
        unsigned int vertexShader;
        unsigned int fragmentShader;

        void CompileShader(const std::string& shaderPath, unsigned int shader);
};