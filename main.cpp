#include "Window.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
{
	GLint screenWidth = 800.f, screenHeight = 800.f;
	Window window(Window::Size(screenWidth, screenHeight), "Hi");

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	std::vector<GLfloat> vertices = {
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
	};

	Shader vertexShader("assets//shaders//main.vert", Gl::Shader::Type::VERTEX);
	Shader fragmentShader("assets//shaders//main.frag", Gl::Shader::Type::FRAGMENT);

	ShaderProgram shaderProgram(vertexShader.getShader(), fragmentShader.getShader());

	VBO vbo(vertices);
	VAO vao(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::perspective(45.0f, (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);

	while (!window.shouldClose())
	{
		window.pollEvents();

		window.clearColor(0.2f, 0.3f, 0.3f, 1.0f);
		window.clear(GL_COLOR_BUFFER_BIT);

		shaderProgram.use();

		// camera
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

		glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

		GLfloat radius = 10.0f;
		GLfloat camX = sin(glfwGetTime()) * radius;
		GLfloat camZ = cos(glfwGetTime()) * radius;
		view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));


		model = glm::rotate(glm::mat4(1.0f), -55.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		//view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

		// load matrices to GPU
		GLint modelLoc = glGetUniformLocation(shaderProgram.getProgram(), "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		GLint viewLoc = glGetUniformLocation(shaderProgram.getProgram(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		GLint projLoc = glGetUniformLocation(shaderProgram.getProgram(), "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		vao.bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		window.swapBuffers(window.getWinTarget());
	}

	return 0;
}

//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//
//	GLfloat cameraSpeed = 0.05f;
//	if(key == GLFW_KEY_W)
//		cameraPos += cameraSpeed * cameraFront;
//	if(key == GLFW_KEY_S)
//		cameraPos -= cameraSpeed * cameraFront;
//	if(key == GLFW_KEY_A)
//		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//	if(key == GLFW_KEY_D)
//		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//}