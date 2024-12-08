#pragma once

#include <glad/glad.h>

#include <rendering/window/VBO/VBO.hpp>

class VAO {
    public:
        GLuint ID;

        VAO();
        void LinkVBO(VBO& VBO, GLuint layout);
        void Bind();
        void Unbind();
        void Delete();
};