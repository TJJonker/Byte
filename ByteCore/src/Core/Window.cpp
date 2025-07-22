#include "ByteCore/Core/Window.h"
#include <iostream>

namespace Byte {
    void Window::Initialize()
    {
        // Check whether glfw is initialized
        if (!glfwInit())
            std::cerr << "Failed to init GLFW\n";

        // Set glfw versions
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // Match your GLAD version
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    }

    void Window::ShutDown()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Window::CreateWindow(int width, int height, const char* name)
    {
        // Create a window
        window = glfwCreateWindow(width, height, name, nullptr, nullptr);
        // Check if window is initialized correctly
        if (!window) {
            std::cerr << "Failed to create GLFW window\n";
            glfwTerminate();
        }

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSwapInterval(1); // Enable vsync

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD\n";
        }

        glClearColor(0.1f, 0.12f, 0.15f, 1.0f); // TODO: Remove
    }

    void Window::PollEvents()
    {
        glfwPollEvents();
    }



    void Window::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::SwapBuffer()
    {
        glfwSwapBuffers(window);
    }

    void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}