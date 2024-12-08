#pragma once

#include <string>
#include <glad/glad.h>

char* ReadFile(const std::string& filename);

GLenum glCheckError_(const char* file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)