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
		-size, -size, -size,
		size, -size, -size,
		size, size, -size,
		size, size, -size,
		-size, size, -size,
		-size, -size, -size,

		-size, -size, size,
		size, -size, size,
		size, size, size,
		size, size, size,
		-size, size,size,
		-size, -size, size,

		-size, size, size,
		-size, size, -size,
		-size, -size, -size,
		-size, -size, -size,
		-size, -size, size,
		-size, size, size,

		size, size, size,
		size, size, -size,
		size, -size, -size,
		size, -size, -size,
		size, -size, size,
		size, size, size,

		-size, -size, -size,
		size, -size, -size,
		size, -size, size,
		size, -size, size,
		-size, -size, size,
		-size, -size, -size,

		-size, size, -size,
		size, size, -size,
		size, size, size,
		size, size, size,
		-size,size, size,
		-size,size, -size
	};

	// setup VAO & VBO
	VBO vbo(vertices);
	VAO vao(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

	// create and setup camera
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // move to 'Camera'
	glm::vec3 cameraPos = glm::vec3(0.f, 0.f, 0.f); // move to 'Camera'
	Camera camera(cameraPos, up);

	// Create model, view and projection matrices
	// glm::mat4 model = glm::rotate(model, -55.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 model = glm::mat4(1.f);
	glm::mat4 view = glm::mat4(1); // move to 'Camera'
	glm::mat4 projection = glm::perspective(glm::radians(90.f), (float)windowWidth / (float)windowHeight, 1.f, 10000.f); // move to 'Camera'

	view = glm::translate(view, glm::vec3(0.f, 0.f, -400.f));

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
		xOffset = 0.f; // move to 'Camera'
		yOffset = 0.f; // move to 'Camera'

		window.pollEvents();

		window.clearColor(0.4f, 0.3f, 0.2f, 1.0f);
		window.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.use();

		//update window size;
		glfwGetFramebufferSize(window.getWinTarget(), &windowWidth, &windowHeight); // move to 'Camera'
		projection = glm::perspective(glm::radians(90.f), (float)windowWidth / (float)windowHeight, 1.f, 1000.f); // move to 'Camera'

		// control camera
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
//
		cameraControl(camera, deltaTime);
		view = camera.getViewMatrix(); // move to 'Camera'

		std::cout << xOffset << std::endl;

		// load matrices to GPU
		GLint modelLoc = glGetUniformLocation(shaderProgram.getProgram(), "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		GLint viewLoc = glGetUniformLocation(shaderProgram.getProgram(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		GLint projLoc = glGetUniformLocation(shaderProgram.getProgram(), "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		GLint ambientIntenseLoc = glGetUniformLocation(shaderProgram.getProgram(), "uAmbientIntense");
		glUniform1f(ambientIntenseLoc, light._ambient.getAmbientIntense());

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
		camera.processKeyboard(Camera::CameraMovement::FORWARD, deltaTime);
	if (GetAsyncKeyState('S') & 0x8000)
		camera.processKeyboard(Camera::CameraMovement::BACKWARD, deltaTime);
	if (GetAsyncKeyState('D') & 0x8000)
		camera.processKeyboard(Camera::CameraMovement::RIGHT, deltaTime);
	if (GetAsyncKeyState('A') & 0x8000)
		camera.processKeyboard(Camera::CameraMovement::LEFT, deltaTime);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) // move to 'Camera'
{
	static GLfloat lastX = 400, lastY = 300;
	xOffset = (GLfloat)xpos - lastX;
	yOffset = lastY - (GLfloat)ypos;
	lastX = (GLfloat)xpos;
	lastY = (GLfloat)ypos;
}