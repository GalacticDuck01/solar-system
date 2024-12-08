#include <rendering/window/VBO/VBO.hpp>

#include <utilities/utilities.hpp>

VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    
    glCheckError();
}

void VBO::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glCheckError();
}

void VBO::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glCheckError();
}

void VBO::Delete() { 
    glDeleteBuffers(1, &ID);
    glCheckError();
}