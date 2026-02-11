#pragma once
#include <glad/glad.h>
#include <string>

class Shader
{
public:
	unsigned int ID; // OpenGL Program ID

	Shader(const char* vertexPath, const char* fragmentPath);
	void Use();

	// Utility uniform functions for later
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;

private:
	void CheckCompileErrors(unsigned int shader, std::string type);
};

