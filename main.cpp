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

int main()
{
	GLint screenWidth = 1280.f, screenHeight = 720.f;
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
	Cube cube1;
	cube.setPosition(glm::vec3(0, 0, 0));
	cube1.setPosition(glm::vec3(0, 0, 0));

	glm::vec3 lightingPosition {1000.f, 0.f, 0.f};

	// create and setup camera
	Camera camera(glm::vec3(0.f, 0.f, 0.f), true);

	GLfloat deltaTime = 0.f;
	GLfloat lastFrame = 0.f;
	GLfloat currentFrame = 0.f;

	Lighting light;
	light._ambient.setAmbientIntense(0.8f);

	GLfloat xOffset = 0.f, yOffset = 0.f;

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glfwSetInputMode(Window::instance().getWinTarget(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);


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

		shaderProgram.uniform("uCameraPos", camera.getPosition());

		shaderProgram.uniform("view", 1, GL_FALSE, camera.getViewMatrix());
		shaderProgram.uniform("projection", 1, GL_FALSE, camera.getProjectionMatrix(
			(GLfloat)Window::instance().getSize().getX(),
			(GLfloat)Window::instance().getSize().getY()));
		shaderProgram.uniform("uAmbientIntense", light._ambient.getAmbientIntense());
		shaderProgram.uniform("uLightingPosition", lightingPosition.x, lightingPosition.y, lightingPosition.z);

		cube.draw("main", &shaderProgram, camera);
		cube1.draw("main", &shaderProgram, camera);

		Window::instance().swapBuffers(Window::instance().getWinTarget());
	}

	return 0;
}