#include <iostream>
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

#include "gui.h"
#include <vector>

void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{

}

void glfw_error_callback(int error, const char *description)
{
    std::cout << "error code: " << error << " " << description << std::endl;
}

int main(int argv, char *argc[])
{
	// Initialize glfw.
    glfwInit();
    glfwSetErrorCallback(glfw_error_callback);

	// Set glfw window hints.  OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create the glfw window.
    GLFWwindow *window = glfwCreateWindow(640, 480, "Fractal", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "ERROR:INITIALIZATION:GLFW" << std::endl;
		return 1;
	}

	// Make the OpenGL context current.
    glfwMakeContextCurrent(window);

	// Initialize the OpenGL functions.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR:INITIALIZATION:GLAD" << std::endl;
		return 1;
	}

    ImGui_ImplGlfwGL3_Init(window, true);
	gui_init();

    while (!glfwWindowShouldClose(window))
	{
        glfwPollEvents();
        ImGui_ImplGlfwGL3_NewFrame();

        glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
		gui_main(window);
        ImGui::Render();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}