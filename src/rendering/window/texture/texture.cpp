#include <rendering/window/texture/texture.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <utilities/utilities.hpp>
#include <fstream>
#include <iostream>

Texture::Texture(const char* image, TextureType textureType, GLuint slot, GLenum format, GLenum pixelType) {
    // Check image path exists
    std::ifstream f(image);
    if (!f.good()) {
        std::cout << TEXT_RED << "Error: " << TEXT_YELLOW << "Texture file does not exist: " << image << TEXT_RESET << std::endl;
        return;
    }
    
    type = textureType;
    int textureWidth, textureHeight, numColourChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(image, &textureWidth, &textureHeight, &numColourChannels, 0);

    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0 + slot);
    unit = slot;
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glCheckError();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glCheckError();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, format, pixelType, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);
    glCheckError();

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);
    glCheckError();
}

void Texture::TexUnit(Shader& shader, const char* uniform, GLuint unit) {
    GLuint textureUniformID = glGetUniformLocation(shader.programID, uniform);
    shader.Activate();
    glUniform1i(textureUniformID, unit);
    glCheckError();
}

void Texture::Bind() {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete() {
    glDeleteTextures(1, &id);
}