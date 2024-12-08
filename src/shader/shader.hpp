#pragma once

#include <glad/glad.h>

class Shader { 
    public:
        GLuint programID;

        Shader(const char* vertexFilePath, const char* fragmentFilePath);
        void Activate();
        void Delete();
};