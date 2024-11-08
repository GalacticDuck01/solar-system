#include <utilities/utilities.hpp>

#include <fstream>
#include <iostream>

char* readFile(const std::string& filename) {
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