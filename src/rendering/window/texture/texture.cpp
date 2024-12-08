#include <rendering/window/texture/texture.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <utilities/utilities.hpp>
#include <fstream>
#include <iostream>

Texture::Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixelType) {
    // Check image path exists
    std::ifstream f(image);
    if (!f.good()) {
        std::cout << TEXT_RED << "Error: " << TEXT_YELLOW << "Texture file does not exist: " << image << TEXT_RESET << std::endl;
        return;
    }
    
    type = texType;
    int textureWidth, textureHeight, numColourChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(image, &textureWidth, &textureHeight, &numColourChannels, 0);

    glGenTextures(1, &id);
    glActiveTexture(slot);
    glBindTexture(texType, id);
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glCheckError();

    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glCheckError();

    glTexImage2D(texType, 0, GL_RGBA, textureWidth, textureHeight, 0, format, pixelType, bytes);
    glGenerateMipmap(texType);
    glCheckError();

    stbi_image_free(bytes);
    glBindTexture(texType, 0);
    glCheckError();
}

void Texture::TexUnit(Shader& shader, const char* uniform, GLuint unit) {
    GLuint textureUniformID = glGetUniformLocation(shader.programID, uniform);
    shader.Activate();
    glUniform1i(textureUniformID, unit);
    glCheckError();
}

void Texture::Bind() {
    glBindTexture(type, id);
}

void Texture::Unbind() {
    glBindTexture(type, 0);
}

void Texture::Delete() {
    glDeleteTextures(1, &id);
}