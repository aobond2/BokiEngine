#pragma once
#include <GLFW/glfw3.h>
#include <memory>
#include "Shader.h"

class Engine
{
public:
	Engine();
	~Engine();

	bool Initialize(int width, int height, const char* title);
	void Run();
	void Shutdown();

private:
	GLFWwindow* m_Window = nullptr;
	bool m_IsRunning = false;

	// Helper to keep main loop clean
	void ProcessInput();
	void Render();

	unsigned int VAO, VBO;
	Shader* myShader;
};
