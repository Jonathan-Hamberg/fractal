#pragma once

#include <string>

#include "glad/glad.h"

class Shader
{
public:
	Shader();
	Shader(std::string path);
	~Shader();

	void Use();
private:
	GLuint _program_shader;
	GLuint _vertex_shader;
	GLuint _fragment_shader;
};