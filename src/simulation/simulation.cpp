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

    GLfloat vertices[] ={
    //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};

    GLuint indices[] = {
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};

    GLfloat lightVertices[] = { 
        //     COORDINATES     //
        -0.1f, -0.1f,  0.1f,
        -0.1f, -0.1f, -0.1f,
         0.1f, -0.1f, -0.1f,
         0.1f, -0.1f,  0.1f,
        -0.1f,  0.1f,  0.1f,
        -0.1f,  0.1f, -0.1f,
         0.1f,  0.1f, -0.1f,
         0.1f,  0.1f,  0.1f
    };

    GLuint lightIndices[] = {
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

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11*sizeof(float), (void*)0); // vertex positions
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11*sizeof(float), (void*)(3*sizeof(float))); // vertex colours
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11*sizeof(float), (void*)(6*sizeof(float))); // texture coordinates
    VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11*sizeof(float), (void*)(8*sizeof(float))); // texture coordinates

    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    Shader lightShader("C:/Users/samru/Desktop/code/solar-system/shaders/light.vert", "C:/Users/samru/Desktop/code/solar-system/shaders/light.frag");
    VAO lightVAO;
    lightVAO.Bind();

    VBO lightVBO(lightVertices, sizeof(lightVertices));
    EBO lightEBO(lightIndices, sizeof(lightIndices));

    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();

    glm::vec4 lightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.programID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.programID, "lightColour"), lightColour.x, lightColour.y, lightColour.z, lightColour.w);
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.programID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
    glUniform4f(glGetUniformLocation(shaderProgram.programID, "lightColour"), lightColour.x, lightColour.y, lightColour.z, lightColour.w);
    glUniform3f(glGetUniformLocation(shaderProgram.programID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    GLuint uniformID = glGetUniformLocation(shaderProgram.programID, "scale"); // Gets the id of the uniform "scale"

    Texture brick("C:/Users/samru/Desktop/code/solar-system/resources/textures/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    brick.TexUnit(shaderProgram, "tex0", 0);

    Camera camera(window.width, window.height, glm::vec3(0.0f, 0.0f, 2.0f));

    // Main loop
    while (!window.ShouldClose()) {
        camera.HandleInputs(window.window);
        window.Render(camera, sizeof(indices)/sizeof(GLuint), shaderProgram, VAO1, brick, sizeof(lightIndices)/sizeof(GLuint), lightShader, lightVAO);
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    brick.Delete();
    shaderProgram.Delete();
}