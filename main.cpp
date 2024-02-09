#include "Window.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>



int main()
{
	Window window(Window::Size(800, 800), "Hi");

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	std::vector<float> vertices = {
		// first triangle
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f,  0.5f, 0.0f,  // top left
		// second triangle
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left
	};

	Shader vertexShader("assets//shaders//main.vert", Gl::Shader::Type::VERTEX);
	Shader fragmentShader("assets//shaders//main.frag", Gl::Shader::Type::FRAGMENT);

	ShaderProgram shaderProgram(vertexShader.getShader(), fragmentShader.getShader());

	VBO vbo(vertices);
	VAO vao(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

	while (!window.shouldClose())
	{
		window.clearColor(0.2f, 0.3f, 0.3f, 1.0f);
		window.clear(GL_COLOR_BUFFER_BIT);

		shaderProgram.use();
		vao.bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);

		window.swapBuffers(window.getWinTarget());
		window.pollEvents();
	}


	return 0;
}
