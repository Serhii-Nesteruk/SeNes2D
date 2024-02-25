#include "Window.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "Lighting.h"
#include "Cube.h"

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
	Window::instance().initializeGLFWVersion();
	Window::instance().create(Window::Size(screenWidth, screenHeight), "Hi");
	Window::instance().makeContextCurrent();

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
	glfwGetFramebufferSize(Window::instance().getWinTarget(), &windowWidth, &windowHeight);
	// shaderProgram.uniform("uWindowSize", static_cast<GLfloat>(windowWidth), static_cast<GLfloat>(windowHeight));

	Cube cube;
// float size = 100.f;
// std::vector<GLfloat> vertices = {
// 	// Передня грань (Front face)
// 	-size, -size, size,    // 1
// 	0.0f, 0.0f, 1.0f,      // Нормаль
// 	size, -size, size,     // 2
// 	0.0f, 0.0f, 1.0f,      // Нормаль
// 	size, size, size,      // 3
// 	0.0f, 0.0f, 1.0f,      // Нормаль
// 	-size, size, size,     // 4
// 	0.0f, 0.0f, 1.0f,      // Нормаль
// 	-size, -size, size,    // 5
// 	0.0f, 0.0f, 1.0f,      // Нормаль
// 	size, size, size,      // 6
// 	0.0f, 0.0f, 1.0f,      // Нормаль

// 	// Задня грань (Back face)
// 	-size, -size, -size,   // 7
// 	0.0f, 0.0f, -1.0f,     // Нормаль
// 	size, -size, -size,    // 8
// 	0.0f, 0.0f, -1.0f,     // Нормаль
// 	size, size, -size,     // 9
// 	0.0f, 0.0f, -1.0f,     // Нормаль
// 	-size, size, -size,    // 10
// 	0.0f, 0.0f, -1.0f,     // Нормаль
// 	-size, -size, -size,   // 11
// 	0.0f, 0.0f, -1.0f,     // Нормаль
// 	size, size, -size,     // 12
// 	0.0f, 0.0f, -1.0f,     // Нормаль

// 	// Ліва грань (Left face)
// 	-size, size, size,     // 13
// 	-1.0f, 0.0f, 0.0f,     // Нормаль
// 	-size, size, -size,    // 14
// 	-1.0f, 0.0f, 0.0f,     // Нормаль
// 	-size, -size, -size,   // 15
// 	-1.0f, 0.0f, 0.0f,     // Нормаль
// 	-size, -size, size,    // 16
// 	-1.0f, 0.0f, 0.0f,     // Нормаль
// 	-size, size, size,     // 17
// 	-1.0f, 0.0f, 0.0f,     // Нормаль
// 	-size, -size, -size,   // 18
// 	-1.0f, 0.0f, 0.0f,     // Нормаль

// 	// Права грань (Right face)
// 	size, size, size,      // 19
// 	1.0f, 0.0f, 0.0f,      // Нормаль
// 	size, size, -size,     // 20
// 	1.0f, 0.0f, 0.0f,      // Нормаль
// 	size, -size, -size,    // 21
// 	1.0f, 0.0f, 0.0f,      // Нормаль
// 	size, -size, size,     // 22
// 	1.0f, 0.0f, 0.0f,      // Нормаль
// 	size, size, size,      // 23
// 	1.0f, 0.0f, 0.0f,      // Нормаль
// 	size, -size, -size,    // 24
// 	1.0f, 0.0f, 0.0f,      // Нормаль

// 	// Верхня грань (Top face)
// 	-size, size, size,     // 25
// 	0.0f, 1.0f, 0.0f,      // Нормаль
// 	size, size, size,      // 26
// 	0.0f, 1.0f, 0.0f,      // Нормаль
// 	size, size, -size,     // 27
// 	0.0f, 1.0f, 0.0f,      // Нормаль
// 	-size, size, -size,    // 28
// 	0.0f, 1.0f, 0.0f,      // Нормаль
// 	-size, size, size,     // 29
// 	0.0f, 1.0f, 0.0f,      // Нормаль
// 	size, size, -size,     // 30
// 	0.0f, 1.0f, 0.0f,      // Нормаль

// 	// Нижня грань (Bottom face)
// 	-size, -size, size,    // 31
// 	0.0f, -1.0f, 0.0f,     // Нормаль
// 	size, -size, size,     // 32
// 	0.0f, -1.0f, 0.0f,     // Нормаль
// 	size, -size, -size,    // 33
// 	0.0f, -1.0f, 0.0f,     // Нормаль
// 	-size, -size, -size,   // 34
// 	0.0f, -1.0f, 0.0f,     // Нормаль
// 	-size, -size, size,    // 35
// 	0.0f, -1.0f, 0.0f,     // Нормаль
// 	size, -size, -size,    // 36
// 	0.0f, -1.0f, 0.0f      // Нормаль
// };

	// setup VAO & VBO
	VBO vbo(cube.getVertices());
	VAO vao(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	Gl::VAO::vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));

	vao.bind();
	vbo.bind();

	glm::vec3 lightingPosition {1000.f, 0.f, 0.f};

	// create and setup camera
	Camera camera(glm::vec3(0.f, 0.f, 0.f), true);

	GLfloat deltaTime = 0.f;
	GLfloat lastFrame = 0.f;
	GLfloat currentFrame = 0.f;

	Lighting light;
	light._ambient.setAmbientIntense(0.8f);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	while (!Window::instance().shouldClose())
	{
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		xOffset = 0.f; // move to 'Camera'
		yOffset = 0.f; // move to 'Camera'

		Window::instance().pollEvents();

		Window::instance().clearColor(0.4f, 0.3f, 0.2f, 1.0f);
		Window::instance().clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.use();

		camera.control(deltaTime);

		cube.draw("main", &shaderProgram, camera);

		// load matrices to GPU
		// GLint modelLoc = glGetUniformLocation(shaderProgram.getProgram(), "model");
		// glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(camera.getModelMatrix())); // *

		// GLint viewLoc = glGetUniformLocation(shaderProgram.getProgram(), "view");
		// glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix())); // *

		// GLint projLoc = glGetUniformLocation(shaderProgram.getProgram(), "projection");
		// glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera.getProjectionMatrix((GLfloat)windowWidth, (GLfloat)windowHeight))); // *

		GLint ambientIntenseLoc = glGetUniformLocation(shaderProgram.getProgram(), "uAmbientIntense");
		glUniform1f(ambientIntenseLoc, light._ambient.getAmbientIntense());

		GLint lightingPositionLoc = glGetUniformLocation(shaderProgram.getProgram(), "uLightingPosition");
		glUniform3f(lightingPositionLoc, lightingPosition.x, lightingPosition.y, lightingPosition.z);

		//vao.bind();
		//vbo.bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		Window::instance().swapBuffers(Window::instance().getWinTarget());
	}

	return 0;
}