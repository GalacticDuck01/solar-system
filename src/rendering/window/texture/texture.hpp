#pragma once

#include <glad/glad.h>
#include <shader/shader.hpp>

class Texture {
    public:
        GLuint id;
        GLuint type;
        GLuint unit;
        
        Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixelType);

        void TexUnit(Shader& shader, const char* uniform, GLuint unit);
        void Bind();
        void Unbind();
        void Delete();
};