#include <rendering/window/EBO/EBO.hpp>
#include <utilities/utilities.hpp>

EBO::EBO(GLuint* indices, GLsizeiptr size) {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    
    glCheckError();
}

void EBO::Bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glCheckError();
}

void EBO::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glCheckError();
}

void EBO::Delete() { 
    glDeleteBuffers(1, &ID);
    glCheckError();
}