#include <rendering/window/window.hpp>

#include <iostream>
#include <tuple>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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

    // To ensure the correct ordering of textures
    glEnable(GL_DEPTH_TEST);

    // Final check for errors
    glCheckError();
}

void Window::Render(Camera& camera, Mesh& floor, Shader& floorShader, Mesh& light, Shader& lightShader) {
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.UpdateMatrix(45.0f, 0.1f, 100.0f);

    floor.Draw(floorShader, camera);
    light.Draw(lightShader, camera);

    glfwSwapBuffers(window);

    glfwPollEvents();
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