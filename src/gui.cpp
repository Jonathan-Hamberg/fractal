#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include "imgui.h"

#include "glType.h"
#include "shader.h"
#include "texture.h"
#include "gui.h"

GLuint VAO, VBO, EBO;
Shader default_shader;
std::vector<glm::u8vec3> texture_data;
Texture texture;


void gui_init()
{
	// Load the shader for rendering.
	default_shader = Shader("shader/default");

	// Allocate memory for the texture.
	texture_data.resize(100*100);

	// Assign random numbers to the texture data.
	for (int i = 0; i < 100 * 100; i++)
	{
		texture_data[i] = glm::vec3(rand() % 255, rand() % 255, rand() % 255);
	}

	texture = Texture(100, 100, texture_data.data());

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	VertexPos2Tex2 vertices[] = {
		{ 0.5f,  0.5f,  1.0f, 1.0f },   // Top Right
		{ 0.5f, -0.5f,  1.0f, 0.0f },   // Bottom Right
		{ -0.5f, -0.5f,  0.0f, 0.0f },   // Bottom Left
		{ -0.5f,  0.5f,  0.0f, 1.0f }    // Top Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,   // First Triangle
		1, 2, 3    // Second Triangle
	};

	glBindVertexArray(VAO);
	// Send the verticies to the GPU.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	VertexPos2Tex2::VertexAttrib();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.ID());
	glUniform1i(glGetUniformLocation(default_shader.ID(), "testing"), 0);

	default_shader.Use();

	glBindVertexArray(0);
}

void gui_main(GLFWwindow *window)
{


	// Get the screen size.
	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	// Set up the main menu for the application.
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("Open", "CTRL+O");
			ImGui::MenuItem("About", nullptr);
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}



	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
