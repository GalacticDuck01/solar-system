#include <rendering/window/VAO/VAO.hpp>

#include <utilities/utilities.hpp>

#include <iostream>

VAO::VAO() {
    glGenVertexArrays(1, &ID);
    glCheckError();
}

void VAO::LinkVBO(VBO& VBO, GLuint layout) {
    VBO.Bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(layout);
    glCheckError();
    VBO.Unbind();
}

void VAO::Bind() {
    glBindVertexArray(ID);
    glCheckError();
}

void VAO::Unbind() {
    glBindVertexArray(0);
    glCheckError();
}

void VAO::Delete() {
    glDeleteVertexArrays(1, &ID);
    glCheckError();
}