#pragma once

#include <string>
#include <map>

#include "glad/glad.h"

class Shader
{
public:
	Shader();
	Shader(std::string path);
	~Shader();

	GLint GetUniform(std::string name);
	void Uniform1i(const char *name, GLint value);
	void Use();
	GLint ID();
private:
	GLuint _program_shader;
	GLuint _vertex_shader;
	GLuint _fragment_shader;
	std::map<std::string, GLint> uniform_map;
};