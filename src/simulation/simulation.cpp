#include <simulation/simulation.hpp>

#include <math.h>

#include <rendering/window/texture/texture.hpp>
#include <rendering/window/VAO/VAO.hpp>
#include <rendering/window/VBO/VBO.hpp>
#include <rendering/window/EBO/EBO.hpp>
#include <shader/shader.hpp>
#include <utilities/utilities.hpp>
#include <camera/camera.hpp>

#include <iostream>

/**
 * @brief Runs the main loop for the simulation.
 *
 * This continues to run until the user closes the window.
 * It is responsible for processing any user input to the window.
 */
void Simulation::Run() {
    Shader shaderProgram("C:/Users/samru/Desktop/code/solar-system/shaders/default.vert", "C:/Users/samru/Desktop/code/solar-system/shaders/default.frag");

    GLfloat vertices[] = {
        // x, y, z, r, g, b, texture u, texture v
        -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
        -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
        0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
        0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
        0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
    };

    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

    VAO VAO;
    VAO.Bind();

    VBO VBO(vertices, sizeof(vertices));
    EBO EBO(indices, sizeof(indices));

    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0); // vertex positions
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float))); // vertex colours
    VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float))); // texture coordinates

    // Unbind all to prevent accidentally modifying them
    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();

    GLuint uniformID = glGetUniformLocation(shaderProgram.programID, "scale"); // Gets the id of the uniform "scale"

    Texture brick("C:/Users/samru/Desktop/code/solar-system/resources/textures/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    brick.TexUnit(shaderProgram, "tex0", 0);

    Camera camera(window.width, window.height, glm::vec3(0.0f, 0.0f, 2.0f));

    // Main loop
    while (!window.ShouldClose()) {
        camera.HandleInputs(window.window);

        window.Render(camera, sizeof(indices)/sizeof(GLuint), shaderProgram, VAO, brick);
    }

    VAO.Delete();
    VBO.Delete();
    EBO.Delete();
    brick.Delete();
    shaderProgram.Delete();
}