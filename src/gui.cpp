#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "imgui.h"

#include "util.h"
#include "glType.h"
#include "shader.h"
#include "texture.h"
#include "mandlebrot.h"
#include "gui.h"

void gui_init(GameData &data)
{
	// Load the shader for rendering.
	data.default_shader = Shader("res/shader/default");

	glGenVertexArrays(1, &data.VAO);
	glGenBuffers(1, &data.VBO);
	glGenBuffers(1, &data.EBO);

	VertexPos2Tex2 vertices[] = {
		{ 1.0f,  1.0f,  1.0f, 1.0f },   // Top Right
		{ 1.0f, -1.0f,  1.0f, 0.0f },   // Bottom Right
		{ -1.0f, -1.0f,  0.0f, 0.0f },   // Bottom Left
		{ -1.0f,  1.0f,  0.0f, 1.0f }    // Top Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3,   // First Triangle
		1, 2, 3    // Second Triangle
	};

	glBindVertexArray(data.VAO);
		glBindBuffer(GL_ARRAY_BUFFER, data.VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, data.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		VertexPos2Tex2::VertexAttrib();
	glBindVertexArray(0);
}

void gui_main(GLFWwindow *window, GameData &data)
{
	// Get the screen size.
	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	data.renderTime = 0.0;
	data.iterations = 128;
	data.render_scale = 1;

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

	static bool settings = true;
	ImGui::SetWindowPos(ImVec2(0.0f, 19.0f));
	ImGui::SetWindowSize(ImVec2(150.0f, windowHeight - 19.0f));
	if (ImGui::Begin("Settings", &settings, 0))
	{
		ImGui::LabelText("time", "%1.3f", data.renderTime);

		ImGui::InputInt("iter", &data.iterations);
		data.iterations = data.iterations < 0 ? 0 : data.iterations;
		data.iterations = data.iterations > 255 ? 255 : data.iterations;

		ImGui::InputInt("scale", &data.render_scale);
		data.render_scale = data.render_scale < 1 ? 1 : data.render_scale;
		data.render_scale = data.render_scale > 16 ? 16 : data.render_scale;
	}
	ImGui::End();

	data.default_shader.Use();

	int fwidth = windowWidth, fheight = windowHeight - 19;
	fwidth /= data.render_scale;
	fheight /= data.render_scale;

	// Allocate memory for the texture.
	if (data.texture_data.size() != fwidth*fheight)
	{
		data.texture_data.resize(fwidth * fheight);
		data.step_data.resize(fwidth * fheight);

		data.renderTime = glfwGetTime();
		render_mandlebrot(data.step_data, fwidth, fheight, -2, -2, 2, 2, data.iterations);
		color_mandlebrot(data.step_data, data.texture_data, data.iterations);
		data.renderTime = glfwGetTime() - data.renderTime;

		data.texture_fractal.UpdateData(data.texture_data.data(), fwidth, fheight);
	}


	// Calculate the upper coordinate for the transform.  This new upper coordinate is to avoid rendering over the menubar.
	float y2 = 1 - (19.0f * 2 / windowHeight);
	glm::mat4 transform = linear_transform(-1, 1, -1, 1, // Input coordinate system.
		-1, 1, -1, y2); // Output coordinate system.
	
	data.default_shader.UniformMatrix4fv("transform", transform);

	glBindTexture(GL_TEXTURE_2D, data.texture_fractal.ID());
	glBindVertexArray(data.VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void gui_shutdown(GameData &data)
{

}