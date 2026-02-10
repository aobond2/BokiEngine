#include <glad/glad.h>
#include "Engine.h"
#include <iostream>

Engine::Engine() : m_Window(nullptr), m_IsRunning(false) {}

Engine::~Engine() {
	Shutdown();
}

bool Engine::Initialize(int width, int height, const char* title) {
	if (!glfwInit()) return false;

	m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!m_Window) {
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	m_IsRunning = true;
	return true;
}

void Engine::Run() {
	while (m_IsRunning && !glfwWindowShouldClose(m_Window))
	{
		ProcessInput();
		Render();

		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
}

void Engine::ProcessInput() {
	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		m_IsRunning = false;
}

void Engine::Render() {
	glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Engine::Shutdown() {
	if (m_Window) {
		glfwDestroyWindow(m_Window);
		m_Window = nullptr;
	}
	glfwTerminate();
}