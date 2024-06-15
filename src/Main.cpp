#include <iostream>

#include "JSON.hpp"
#include "root.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "GL/glew.h"

#include "OGL/ShaderProgram/Program.hpp"
#include "Model/ModelFactory.hpp"

void _GLFWDebugCallback(int error_code, const char* description)
{
	if (_DEBUG) __debugbreak();
	std::cout << "GLFW Error (" << error_code << "): " << description << '\n';
}
void __stdcall _GLDebugCallback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userParam)
{
	if (_DEBUG) __debugbreak();
	std::cout << "GL Error Callback: Debug it right now!\n" << message << '\n';
}

int main()
{
	if (!glfwInit())
	{
		throw std::exception("Failed to Initialize GLFW!\n");
	}
	glfwSetErrorCallback(_GLFWDebugCallback);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

	GLFWwindow* window = glfwCreateWindow(900, 900, "Window", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		throw std::exception("Failed to Create a Window!\n");
	}

	glfwMakeContextCurrent(window);

	if (glewInit())
	{
		throw std::exception("Failed to Initialize GLEW!\n");
	}

	glEnable(GL_DEBUG_CALLBACK_FUNCTION);
	glDebugMessageCallback(_GLDebugCallback, nullptr);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	DK::Model cubeModel;
	DK::ModelFactory::initializeUsingGLTF(cubeModel, ROOT_DIR "/src/Resources/Cube", ROOT_DIR "/src/Resources/Cube/Cube.gltf", 0);

	OGL::Program color(ROOT_DIR "/src/Resources/Shaders/Color");
	color.use();
	color.uni4f("uColor", glm::vec4(0.34f, 0.834f, 0.73f, 1.0f));

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		cubeModel.draw(color);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}