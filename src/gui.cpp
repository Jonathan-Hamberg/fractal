#include <iostream>

#include "imgui.h"

#include "shader.h"
#include "gui.h"

GLuint VAO, VBO;
Shader default_shader;

void gui_init()
{
	// Load the shader for rendering.
	default_shader = Shader("shader/default");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
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

	GLfloat vertices[] = {
		// First triangle
		0.5f,  0.5f, 0.0f,  // Top Right
		0.5f, -0.5f, 0.0f,  // Bottom Right
	   -0.5f,  0.5f, 0.0f,  // Top Left 
							 // Second triangle
		0.5f, -0.5f, 0.0f,  // Bottom Right
	   -0.5f, -0.5f, 0.0f,  // Bottom Left
	   -0.5f,  0.5f, 0.0f   // Top Left
	};

	glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glUseProgram(default_shader.ProgramID());
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

}
