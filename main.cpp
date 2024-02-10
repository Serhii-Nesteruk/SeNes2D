#include "Window.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

GLfloat xOffset = 0.f;
GLfloat yOffset = 0.f;

void cameraControl(Camera& camera, GLfloat deltaTime);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);

int main()
{
	GLint screenWidth = 800.f, screenHeight = 800.f;
	Window window(Window::Size(screenWidth, screenHeight), "Hi");

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// setting up shaders and the shader program
	Shader vertexShader("assets//shaders//main.vert", Gl::Shader::Type::VERTEX);
	Shader fragmentShader("assets//shaders//main.frag", Gl::Shader::Type::FRAGMENT);

	ShaderProgram shaderProgram(vertexShader.getShader(), fragmentShader.getShader());
	shaderProgram.use();

	GLint windowWidth = 0, windowHeight = 0;
	glfwGetFramebufferSize(window.getWinTarget(), &windowWidth, &windowHeight);
	shaderProgram.uniform("uWindowSize", static_cast<GLfloat>(windowWidth), static_cast<GLfloat>(windowHeight));

	std::vector<GLfloat> vertices = {
		-100, -100, -100,
		100, -100, -100,
		100, 100, -100,
		100, 100, -100,
		-100, 100, -100,
		-100, -100, -100,

		-100, -100, 100,
		100, -100, 100,
		100, 100, 100,
		100, 100, 100,
		-100, 100,100,
		-100, -100, 100,

		-100, 100, 100,
		-100, 100, -100,
		-100, -100, -100,
		-100, -100, -100,
		-100, -100, 100,
		-100, 100, 100,

		100, 100, 100,
		100, 100, -100,
		100, -100, -100,
		100, -100, -100,
		100, -100, 100,
		100, 100, 100,

		-100, -100, -100,
		100, -100, -100,
		100, -100, 100,
		100, -100, 100,
		-100, -100, 100,
		-100, -100, -100,

		-100, 100, -100,
		100, 100, -100,
		100, 100, 100,
		100, 100, 100,
		-100,100, 100,
		-100,100, -100
	};

	// setup VAO & VBO
	VBO vbo(vertices);
	VAO vao(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

	// create and setup camera
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraPos = glm::vec3(0.f, 0.f, -3.f);
	Camera camera(cameraPos, up);

	// Create model, view and projection matrices
	glm::mat4 model = glm::rotate(model, -55.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 view = camera.getViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)windowWidth / (float)windowHeight, 0.001f, 1000.f);

	GLfloat deltaTime = 0.f;
	GLfloat lastFrame = 0.f;
	GLfloat currentFrame = 0.f;

	// glfwSetInputMode(window.getWinTarget(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window.getWinTarget(), mouseCallback);

	glEnable(GL_DEPTH_TEST);

	while (!window.shouldClose())
	{
		window.pollEvents();

		window.clearColor(0.4f, 0.3f, 0.2f, 1.0f);
		window.clear(GL_COLOR_BUFFER_BIT);

		shaderProgram.use();

		// update window size;
		glfwGetFramebufferSize(window.getWinTarget(), &windowWidth, &windowHeight);
		projection = glm::perspective(glm::radians(45.f), (float)windowWidth / (float)windowHeight, 0.001f, 1000.f);

		// control camera
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		cameraControl(camera, deltaTime);
		view = camera.getViewMatrix();

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

void cameraControl(Camera& camera, GLfloat deltaTime)
{
	camera.processMouseMovement(xOffset, yOffset, true);
	if (GetAsyncKeyState('W') & 0x8000)
		camera.processKeyboard(Camera::CameraMovement::FORWARD, deltaTime);
	if (GetAsyncKeyState('S') & 0x8000)
		camera.processKeyboard(Camera::CameraMovement::BACKWARD, deltaTime);
	if (GetAsyncKeyState('D') & 0x8000)
		camera.processKeyboard(Camera::CameraMovement::RIGHT, deltaTime);
	if (GetAsyncKeyState('A') & 0x8000)
		camera.processKeyboard(Camera::CameraMovement::LEFT, deltaTime);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	GLfloat lastX = 400, lastY = 300;
	xOffset = (GLfloat)xpos - lastX;
	yOffset = lastY - (GLfloat)ypos;
	lastX = (GLfloat)xpos;
	lastY = (GLfloat)ypos;
}