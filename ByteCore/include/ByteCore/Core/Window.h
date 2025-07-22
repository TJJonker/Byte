#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Byte {
	class Window {
	public:
		void Initialize();
		void ShutDown();

		void CreateWindow(int width, int height, const char* name);
		void PollEvents();

		void Clear();
		void SwapBuffer();

		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

		GLFWwindow* GetWindow() { return window; }
		bool ShouldClose() { return glfwWindowShouldClose(window); }

	private:
		GLFWwindow* window;
	};
}