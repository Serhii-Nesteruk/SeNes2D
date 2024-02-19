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

class Lighting
{
public:
	struct Ambient
	{
	public:
		void setAmbientIntense(GLfloat ambientIntense)
		{
			_ambientIntense = std::clamp(ambientIntense, 0.f, 1.f);
		}
		GLfloat getAmbientIntense() const
		{
			return _ambientIntense;
		}
	private:
		GLfloat _ambientIntense = 0.f;
	} _ambient;
};

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
	// shaderProgram.uniform("uWindowSize", static_cast<GLfloat>(windowWidth), static_cast<GLfloat>(windowHeight));

	float size = 100.f;
	std::vector<GLfloat> vertices = {
		// Передня грань (Front face)
		-size, -size, size,    // 1
		0.0f, 0.0f, 1.0f,      // Нормаль
		size, -size, size,     // 2
		0.0f, 0.0f, 1.0f,      // Нормаль
		size, size, size,      // 3
		0.0f, 0.0f, 1.0f,      // Нормаль
		-size, size, size,     // 4
		0.0f, 0.0f, 1.0f,      // Нормаль
		-size, -size, size,    // 5
		0.0f, 0.0f, 1.0f,      // Нормаль
		size, size, size,      // 6
		0.0f, 0.0f, 1.0f,      // Нормаль

		// Задня грань (Back face)
		-size, -size, -size,   // 7
		0.0f, 0.0f, -1.0f,     // Нормаль
		size, -size, -size,    // 8
		0.0f, 0.0f, -1.0f,     // Нормаль
		size, size, -size,     // 9
		0.0f, 0.0f, -1.0f,     // Нормаль
		-size, size, -size,    // 10
		0.0f, 0.0f, -1.0f,     // Нормаль
		-size, -size, -size,   // 11
		0.0f, 0.0f, -1.0f,     // Нормаль
		size, size, -size,     // 12
		0.0f, 0.0f, -1.0f,     // Нормаль

		// Ліва грань (Left face)
		-size, size, size,     // 13
		-1.0f, 0.0f, 0.0f,     // Нормаль
		-size, size, -size,    // 14
		-1.0f, 0.0f, 0.0f,     // Нормаль
		-size, -size, -size,   // 15
		-1.0f, 0.0f, 0.0f,     // Нормаль
		-size, -size, size,    // 16
		-1.0f, 0.0f, 0.0f,     // Нормаль
		-size, size, size,     // 17
		-1.0f, 0.0f, 0.0f,     // Нормаль
		-size, -size, -size,   // 18
		-1.0f, 0.0f, 0.0f,     // Нормаль

		// Права грань (Right face)
		size, size, size,      // 19
		1.0f, 0.0f, 0.0f,      // Нормаль
		size, size, -size,     // 20
		1.0f, 0.0f, 0.0f,      // Нормаль
		size, -size, -size,    // 21
		1.0f, 0.0f, 0.0f,      // Нормаль
		size, -size, size,     // 22
		1.0f, 0.0f, 0.0f,      // Нормаль
		size, size, size,      // 23
		1.0f, 0.0f, 0.0f,      // Нормаль
		size, -size, -size,    // 24
		1.0f, 0.0f, 0.0f,      // Нормаль

		// Верхня грань (Top face)
		-size, size, size,     // 25
		0.0f, 1.0f, 0.0f,      // Нормаль
		size, size, size,      // 26
		0.0f, 1.0f, 0.0f,      // Нормаль
		size, size, -size,     // 27
		0.0f, 1.0f, 0.0f,      // Нормаль
		-size, size, -size,    // 28
		0.0f, 1.0f, 0.0f,      // Нормаль
		-size, size, size,     // 29
		0.0f, 1.0f, 0.0f,      // Нормаль
		size, size, -size,     // 30
		0.0f, 1.0f, 0.0f,      // Нормаль

		// Нижня грань (Bottom face)
		-size, -size, size,    // 31
		0.0f, -1.0f, 0.0f,     // Нормаль
		size, -size, size,     // 32
		0.0f, -1.0f, 0.0f,     // Нормаль
		size, -size, -size,    // 33
		0.0f, -1.0f, 0.0f,     // Нормаль
		-size, -size, -size,   // 34
		0.0f, -1.0f, 0.0f,     // Нормаль
		-size, -size, size,    // 35
		0.0f, -1.0f, 0.0f,     // Нормаль
		size, -size, -size,    // 36
		0.0f, -1.0f, 0.0f      // Нормаль
	};

	// setup VAO & VBO
	VBO vbo(vertices);
	VAO vao(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	Gl::VAO::vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));

	glm::vec3 lightingPosition {1000.f, 0.f, 0.f};

	// create and setup camera
	Camera camera(glm::vec3(0.f, 0.f, 0.f));

	GLfloat deltaTime = 0.f;
	GLfloat lastFrame = 0.f;
	GLfloat currentFrame = 0.f;

	// glfwSetInputMode(window.getWinTarget(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window.getWinTarget(), mouseCallback); // move to 'Camera'

	Lighting light;
	light._ambient.setAmbientIntense(0.8f);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	while (!window.shouldClose())
	{
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		xOffset = 0.f; // move to 'Camera'
		yOffset = 0.f; // move to 'Camera'

		window.pollEvents();

		window.clearColor(0.4f, 0.3f, 0.2f, 1.0f);
		window.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.use();

		cameraControl(camera, deltaTime);

		std::cout << xOffset << std::endl;

		// load matrices to GPU
		GLint modelLoc = glGetUniformLocation(shaderProgram.getProgram(), "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(camera.getModelMatrix())); // *

		GLint viewLoc = glGetUniformLocation(shaderProgram.getProgram(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix())); // *

		GLint projLoc = glGetUniformLocation(shaderProgram.getProgram(), "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera.getProjectionMatrix((GLfloat)windowWidth, (GLfloat)windowHeight))); // *

		GLint ambientIntenseLoc = glGetUniformLocation(shaderProgram.getProgram(), "uAmbientIntense");
		glUniform1f(ambientIntenseLoc, light._ambient.getAmbientIntense());

		GLint lightingPositionLoc = glGetUniformLocation(shaderProgram.getProgram(), "uLightingPosition");
		glUniform3f(lightingPositionLoc, lightingPosition.x, lightingPosition.y, lightingPosition.z);

		vao.bind();
		vbo.bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		window.swapBuffers(window.getWinTarget());
	}

	return 0;
}

void cameraControl(Camera& camera, GLfloat deltaTime) // move to 'Camera'
{
	camera.processMouseMovement(xOffset, yOffset, true);
	if (GetAsyncKeyState('W') & 0x8000)
		camera.processKeyboard(Camera::Movement::FORWARD, deltaTime);
	if (GetAsyncKeyState('S') & 0x8000)
		camera.processKeyboard(Camera::Movement::BACKWARD, deltaTime);
	if (GetAsyncKeyState('D') & 0x8000)
		camera.processKeyboard(Camera::Movement::RIGHT, deltaTime);
	if (GetAsyncKeyState('A') & 0x8000)
		camera.processKeyboard(Camera::Movement::LEFT, deltaTime);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) // move to 'Camera'
{
	static GLfloat lastX = 400, lastY = 300;
	xOffset = (GLfloat)xpos - lastX;
	yOffset = lastY - (GLfloat)ypos;
	lastX = (GLfloat)xpos;
	lastY = (GLfloat)ypos;
}