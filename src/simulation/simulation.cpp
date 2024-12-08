#include <simulation/simulation.hpp>

#include <math.h>

#include <rendering/window/texture/texture.hpp>
#include <rendering/window/VAO/VAO.hpp>
#include <rendering/window/VBO/VBO.hpp>
#include <rendering/window/EBO/EBO.hpp>
#include <shader/shader.hpp>
#include <utilities/utilities.hpp>

GLfloat vertices[] = {
    // x, y, z, r, g, b, texture u, texture v
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Lower left
    -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Upper left
     0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Upper right
     0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f  // Lower right
};

GLuint indices[] = {
    0, 2, 1, // Upper triangle
    0, 3, 2 // Lower triangle
};

/**
 * @brief Runs the main loop for the simulation.
 *
 * This continues to run until the user closes the window.
 * It is responsible for processing any user input to the window.
 */
void Simulation::Run() {
    Shader shaderProgram("C:/Users/samru/Desktop/code/solar-system/shaders/default.vert", "C:/Users/samru/Desktop/code/solar-system/shaders/default.frag");

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

    Texture pop_cat("C:/Users/samru/Desktop/code/solar-system/resources/textures/pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    pop_cat.TexUnit(shaderProgram, "tex0", 0);

    // Main loop
    while (!window.ShouldClose()) {
        window.ProcessInput();

        window.Render(shaderProgram, VAO, uniformID, pop_cat);
    }

    VAO.Delete();
    VBO.Delete();
    EBO.Delete();
    pop_cat.Delete();
    shaderProgram.Delete();
}