#include <rendering/window/mesh/mesh.hpp>

#include <utilities/utilities.hpp>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    vao.Bind();

    VBO vbo(vertices);
    EBO ebo(indices);

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);                 // Coordinates
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3*sizeof(float))); // Colours
    vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6*sizeof(float))); // Normals
    vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9*sizeof(float))); // Texture coordinates

    // Unbind all to prevent accidentally modifying them
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}

void Mesh::Draw(Shader& shader, Camera& camera) {
    shader.Activate();
    vao.Bind();
    unsigned int numOfDiffuseTextures = 0;
    unsigned int numOfSpecularTextures = 0;
    for (unsigned int i = 0; i < textures.size(); i++) {
        std::string num = std::to_string(i);
        TextureType type = textures[i].type;
        if (type == TextureType::DIFFUSE) {
            num = std::to_string(numOfDiffuseTextures++);
        } else if (type == TextureType::SPECULAR) {
            num = std::to_string(numOfSpecularTextures++);
        }

        textures[i].TexUnit(shader, (textures[i].GetTextureTypeAsString() + num).c_str(), i);
        textures[i].Bind();
    }
    glUniform3f(glGetUniformLocation(shader.programID, "camPos"), camera.position.x, camera.position.y, camera.position.z);
    camera.Matrix(shader, "camMatrix");

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
