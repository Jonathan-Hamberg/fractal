#include <vector>
#include <cstdint>
#include <fstream>
#include <iostream>

#include "shader.h"

Shader::Shader()
{
	_vertex_shader = 0;
	_fragment_shader = 0;
	_program_shader = 0;
}

Shader::Shader(std::string path)
{
	std::string vertex_path = path + ".vert";
	std::string fragment_path = path + ".frag";

	std::vector<GLchar> vertex_source;
	std::vector<GLchar> fragment_source;

	// Read the vertex shader to a buffer.
	std::ifstream file(vertex_path, std::ios::binary | std::ios::ate);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	vertex_source.resize(size + 1);
	file.read((char *)vertex_source.data(), size);

	// Read the fragment shader to a buffer.
	file = std::ifstream(fragment_path, std::ios::binary | std::ios::ate);
	size = file.tellg();
	file.seekg(0, std::ios::beg);

	fragment_source.resize(size + 1);
	file.read((char *)fragment_source.data(), size);

	// Create the vertex shader.
	char *source = vertex_source.data();
	_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vertex_shader, 1, &source, 0);
	glCompileShader(_vertex_shader);

	// Check for any errors in the vertex shader.
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(_vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(_vertex_shader, 512, NULL, infoLog);
		std::cout << "ERROR:SHADER:VERTEX:COMPILATION:FAILED\n" << infoLog << std::endl;
	}

	// Create the fragment shader.
	source = fragment_source.data();
	_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_fragment_shader, 1, &source, 0);
	glCompileShader(_fragment_shader);

	// Check for any errors in the fragment shader.
	glGetShaderiv(_fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(_fragment_shader, 512, nullptr, infoLog);
		std::cout << "ERROR:SHADER:FRAGMENT:COMPILATION:FAILED\n" << infoLog << std::endl;
	}

	// Create the program shader.
	_program_shader = glCreateProgram();
	
	// Link the vertex and fragment shader.
	glAttachShader(_program_shader, _vertex_shader);
	glAttachShader(_program_shader, _fragment_shader);
	glLinkProgram(_program_shader);

	// Check for any errors in the linking process.
	glGetProgramiv(_program_shader, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_program_shader, 512, nullptr, infoLog);
		std::cout << "ERROR:SHADER:PROGRAM:LINKING:FAILED\n" << infoLog << std::endl;
	}

	// Delete the shaders as they are no longer necessary because they are already linked.
	glDeleteShader(_vertex_shader);
	glDeleteShader(_fragment_shader);
}

Shader::~Shader()
{

}

void Shader::Use()
{
	glUseProgram(_program_shader);
}
