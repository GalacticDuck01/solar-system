#include <simulation/simulation.hpp>

#include <iostream>
#include <math.h>
#include <vector>

#include <rendering/window/mesh/mesh.hpp>
#include <rendering/window/texture/texture.hpp>
#include <rendering/window/VBO/VBO.hpp>

/**
 * @brief Runs the main loop for the simulation.
 *
 * This continues to run until the user closes the window.
 * It is responsible for processing any user input to the window.
 */
void Simulation::Run() {
   // Vertices coordinates
    Vertex vertices[] = {
    //               COORDINATES           /           NORMALS          /            COLORS          /       TEXTURE COORDINATES    //
        Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)}
    };

    // Indices for vertices order
    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    Vertex lightVertices[] = {
        //     COORDINATES     //
        Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
        Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
        Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
        Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
    };

    unsigned int lightIndices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 4, 7,
        0, 7, 3,
        3, 7, 6,
        3, 6, 2,
        2, 6, 5,
        2, 5, 1,
        1, 5, 4,
        1, 4, 0,
        4, 5, 6,
        4, 6, 7
    };

    Texture textures[] = {
        Texture("C:/Users/samru/Desktop/code/solar-system/resources/textures/planks.png", TextureType::DIFFUSE, 0, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture("C:/Users/samru/Desktop/code/solar-system/resources/textures/planksSpec.png", TextureType::SPECULAR, 1, GL_RED, GL_UNSIGNED_BYTE)
    };

    Shader shaderProgram("C:/Users/samru/Desktop/code/solar-system/shaders/default.vert", "C:/Users/samru/Desktop/code/solar-system/shaders/default.frag");
    std::vector<Vertex> verticesVec(vertices, vertices + sizeof(vertices)/sizeof(Vertex));
    std::vector<unsigned int> indicesVec(indices, indices + sizeof(indices)/sizeof(unsigned int));
    std::vector<Texture> texturesVec(textures, textures + sizeof(textures)/sizeof(Texture));
    Mesh floor(verticesVec, indicesVec, texturesVec);

    Shader lightShader("C:/Users/samru/Desktop/code/solar-system/shaders/light.vert", "C:/Users/samru/Desktop/code/solar-system/shaders/light.frag");
    std::vector<Vertex> lightVerticesVec(lightVertices, lightVertices + sizeof(lightVertices)/sizeof(Vertex));
    std::vector<unsigned int> lightIndicesVec(lightIndices, lightIndices + sizeof(lightIndices)/sizeof(unsigned int));
    Mesh light(lightVerticesVec, lightIndicesVec, texturesVec);

    glm::vec4 lightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 objectModel = glm::mat4(1.0f);
    objectModel = glm::translate(objectModel, objectPos);

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.programID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.programID, "lightColour"), lightColour.x, lightColour.y, lightColour.z, lightColour.w);
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.programID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
    glUniform4f(glGetUniformLocation(shaderProgram.programID, "lightColour"), lightColour.x, lightColour.y, lightColour.z, lightColour.w);
    glUniform3f(glGetUniformLocation(shaderProgram.programID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    Camera camera(window.width, window.height, glm::vec3(0.0f, 0.0f, 2.0f));

    // Main loop
    while (!window.ShouldClose()) {
        camera.HandleInputs(window.window);
        window.Render(camera, floor, shaderProgram, light, lightShader);
    }

    shaderProgram.Delete();
    lightShader.Delete();
}