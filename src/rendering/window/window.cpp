#include <rendering/window/window.hpp>

#include <iostream>

#include <glad/glad.h>
#include <rendering/shader/shader.hpp>

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
    // glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Disable the OpenGL API
    // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Disable window resizing

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
    // glfwSwapInterval(1); // Enable vsync

    // GLAD: Load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Error: Failed to initialize GLAD" << std::endl;
    }

    glfwSetCursorEnterCallback(window, this->CallbackCursorEnter); // Set the callback function for cursor enter/exit events

    Shader shader = Shader("../shaders/base_vertex.glsl", "../shaders/base_fragment.glsl"); // TODO: Currently, paths are relative to executable. Fix this!
    shader.Use();
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
}

void Window::Render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // draw our first triangle
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glBindVertexArray(0); // no need to unbind it every time 

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
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