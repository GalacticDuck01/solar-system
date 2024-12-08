#include <simulation/simulation.hpp>

#include <math.h>

#include <rendering/window/VAO/VAO.hpp>
#include <rendering/window/VBO/VBO.hpp>
#include <rendering/window/EBO/EBO.hpp>
#include <shader/shader.hpp>

GLfloat vertices[] = {
    // x, y, z
    -0.5f,      -0.5f*sqrt(3)/3.f,      0.0f, // Left
    0.5f,       -0.5f*sqrt(3)/3.f,      0.0f, // Right
    0.0f,        0.5f*2.f*sqrt(3)/3.f,  0.0f, // Top
    -0.5f/2.f,   0.5f*sqrt(3)/6.f,      0.0f, // Inner left
    0.5f/2.f,    0.5f*sqrt(3)/6.f,      0.0f, // Inner right
    0.0f,       -0.5f*sqrt(3)/3.f,      0.0f // Inner down

};

GLuint indices[] = {
    0, 3, 5, // Lower left triangle
    3, 2, 4, // Lower right triangle
    5, 4, 1 // Upper triangle
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

    VAO.LinkVBO(VBO, 0);

    // Unbind all to prevent accidentally modifying them
    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();

    // Main loop
    while (!window.ShouldClose()) {
        window.ProcessInput();

        window.Render(shaderProgram, VAO);
    }

    VAO.Delete();
    VBO.Delete();
    EBO.Delete();
    shaderProgram.Delete();
}