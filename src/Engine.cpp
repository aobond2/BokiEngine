#include <glad/glad.h>
#include "Engine.h"
#include <iostream>
#include <filesystem>

Engine::Engine() : m_Window(nullptr), m_IsRunning(false) {}

Engine::~Engine() {
	Shutdown();
}

bool Engine::Initialize(int width, int height, const char* title) {
	std::cout << "Current Path: " << std::filesystem::current_path() << std::endl;
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

	// Vertex data
	float vertices[] = {
		// Position         //Colors
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	// Bottom left
		0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	// Bottom right
		0.0f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f	// Top Center
	};

	myShader = new Shader("C:/Users/aobon_ktnb1ku/Documents/BokiEngine/build/shaders/vertex.glsl",
		"C:/Users/aobon_ktnb1ku/Documents/BokiEngine/build/shaders/fragment.glsl");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind and upload
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Link Attributes
	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

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
	//glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);

	glClear(GL_COLOR_BUFFER_BIT);
	// Activate shader and geometry
	myShader->Use();
	glBindVertexArray(VAO);

	// Draw
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Engine::Shutdown() {
	if (m_Window) {
		glfwDestroyWindow(m_Window);
		m_Window = nullptr;
	}
	glfwTerminate();
}