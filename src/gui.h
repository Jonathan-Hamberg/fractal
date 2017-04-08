#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shader.h"
#include "texture.h"

struct GameData
{
	// Rendering Data.
	Texture texture_fractal;
	Shader default_shader;
	GLuint VAO, VBO, EBO;
	std::vector<glm::u8vec3> texture_data;
	std::vector<uint8_t> step_data;

	// User Interface Data.
	double renderTime = 0.0;
	int iterations = 128;
	int render_scale;
};

void gui_init(GameData &data);
void gui_main(GLFWwindow *window, GameData &data);
void gui_shutdown(GameData &data);