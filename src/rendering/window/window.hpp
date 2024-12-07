#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
    private:
        GLFWwindow* window;
        int width;
        int height;
        std::string name;

        void InitWindow();

        static void CallbackCursorEnter(GLFWwindow* window, int entered);
        static void CallbackFrameworkSize(GLFWwindow* window, int width, int height);

    public:
        bool hasCursorEntered = false;

        Window(int width, int height, std::string name);
        ~Window();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        bool ShouldClose() { return glfwWindowShouldClose(window); }
        void ProcessInput();
        void Render();
};