#pragma once

#include <string>
#include <vector>
#include <rendering/window/VAO/VAO.hpp>
#include <rendering/window/EBO/EBO.hpp>
#include <rendering/window/texture/texture.hpp>
#include <camera/camera.hpp>

class Mesh {
    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        VAO vao;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

        void Draw(Shader& shader, Camera& camera);
};