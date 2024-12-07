#include <rendering/window/window.hpp>

#include <iostream>

#include <glad/glad.h>
#include <utilities/utilities.hpp>

Window::Window(int width, int height, std::string name) {
    this->width = width;
    this->height = height;
    this->name = name;
    InitWindow();
}

/**
 * Destroys the window by calling glfwDestroyWindow and then terminates the GLFW library.
 */
Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

/**
 * Initializes the GLFW window.
 * 
 * This function sets up the window using GLFW, disabling the OpenGL API
 * and making the window non-resizable. It creates a window with the
 * specified width, height, and name.
 * 
 * @throws std::runtime_error If the GLFW library fails to initialize.
 */
void Window::InitWindow() {
    glfwInit(); // Initialize the GLFW library
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Use OpenGL 3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Use the core profile

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL); // Create the GLFW window

    if (window == NULL) {
        std::cout << "Error: Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, this->CallbackFrameworkSize); // Set the callback function for framebuffer size changes

    gladLoadGL();

    // GLAD: Load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Error: Failed to initialize GLAD" << std::endl;
    }
}


/**
 * @brief Processes input for the window.
 *
 * This function checks for key presses and performs actions accordingly.
 * Specifically, it checks if the ESCAPE key is pressed and sets the window
 * to close if it is.
 */
void Window::ProcessInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    glfwPollEvents();
    glCheckError();
}

void Window::Render() {
    glClearColor(0.7f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    
    // Vertex Shader source code
    const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    //Fragment Shader source code
    const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
    "}\n\0";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLfloat vertices[] = {
        // x, y, z, r, g, b
        0.0f, 0.5f, 0.0f, // Top
        0.5f, -0.5f, 0.0f, // Right
        -0.5f, -0.5f, 0.0f, // Left
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glUseProgram(shaderProgram);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
}


/**
 * @brief Callback function for window resize events.
 * 
 * (GLFW) Whenever the window size changes (by the user resizing the window or
 * because the video mode changed) this callback function executes.
 *
 * @param window The window that received the event
 * @param width The new width, in screen coordinates, of the window
 * @param height The new height, in screen coordinates, of the window
 *
 * @remarks We use the new window dimensions to update the OpenGL viewport.
 */
void Window::CallbackFrameworkSize(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    glCheckError();
}

/**
 * @brief Callback function for cursor enter/exit events.
 * 
 * (GLFW) Whenever the cursor enters or leaves the content area of the window this callback function executes
 *
 * @param window The window that received the event
 * @param entered GLFW_TRUE if the cursor entered the content area of the window, otherwise GLFW_FALSE
 */
void Window::CallbackCursorEnter(GLFWwindow* window, int entered) {
    if (entered) {
        // The cursor entered the content area of the window
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        // The cursor left the content area of the window
    }
}