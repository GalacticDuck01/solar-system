#include <fstream>
#include <iostream>

#include <utilities/utilities.hpp>
#include <utilities/colour_output.hpp>

/**
 * Reads the contents of a file and returns a pointer to it.
 *
 * \param filename The name of the file to read.
 * \return A pointer to the contents of the file or nullptr if the file does not exist.
 */
char* ReadFile(const std::string& filename) {
    // Check if file exists
    std::ifstream f(filename);
    if (!f.good()) {
        std::cout << "Error: File does not exist: " << filename << std::endl;
        return nullptr;
    }

    char* buffer = nullptr;
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    buffer = new char[size];
    file.read(buffer, size);
    file.close();
    return buffer;
}

/**
 * \brief Checks for OpenGL errors and prints them to the console if they are encountered.
 * \param file The file that the error occurred in.
 * \param line The line that the error occurred on.
 * \return The error code if an error occurred, otherwise GL_NO_ERROR.
 */
GLenum glCheckError_(const char* file, int line) {
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR) {
        std::string error;
        switch (errorCode) {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            default:                               error = "UNKNOWN_ERROR"; break;
        }
        std::cout << TEXT_RED << "OpenGL Error: " << TEXT_YELLOW << error << TEXT_RESET << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}