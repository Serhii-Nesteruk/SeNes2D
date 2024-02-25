#include "Cube.h"

#include "Camera.h"

Cube::Cube()
{
	setupVertices();
}

void Cube::setSize(GLfloat size)
{
	_size = size;
	setupVertices();
}

GLfloat Cube::getSize() const
{
	return _size;
}

void Cube::setupVertices()
{
	std::vector<GLfloat> vertices = {
		// Front face
		-_size, -_size, _size,
		0.0f, 0.0f, 1.0f,
		_size, -_size, _size,
		0.0f, 0.0f, 1.0f,
		_size, _size, _size,
		0.0f, 0.0f, 1.0f,
		-_size, _size, _size,
		0.0f, 0.0f, 1.0f,
		-_size, -_size, _size,
		0.0f, 0.0f, 1.0f,
		_size, _size, _size,
		0.0f, 0.0f, 1.0f,

		// Back face
		-_size, -_size, -_size,
		0.0f, 0.0f, -1.0f,
		_size, -_size, -_size,
		0.0f, 0.0f, -1.0f,
		_size, _size, -_size,
		0.0f, 0.0f, -1.0f,
		-_size, _size, -_size,
		0.0f, 0.0f, -1.0f,
		-_size, -_size, -_size,
		0.0f, 0.0f, -1.0f,
		_size, _size, -_size,
		0.0f, 0.0f, -1.0f,

		// Left face
		-_size, _size, _size,
		-1.0f, 0.0f, 0.0f,
		-_size, _size, -_size,
		-1.0f, 0.0f, 0.0f,
		-_size, -_size, -_size,
		-1.0f, 0.0f, 0.0f,
		-_size, -_size, _size,
		-1.0f, 0.0f, 0.0f,
		-_size, _size, _size,
		-1.0f, 0.0f, 0.0f,
		-_size, -_size, -_size,
		-1.0f, 0.0f, 0.0f,

		// Right face
		_size, _size, _size,
		1.0f, 0.0f, 0.0f,
		_size, _size, -_size,
		1.0f, 0.0f, 0.0f,
		_size, -_size, -_size,
		1.0f, 0.0f, 0.0f,
		_size, -_size, _size,
		1.0f, 0.0f, 0.0f,
		_size, _size, _size,
		1.0f, 0.0f, 0.0f,
		_size, -_size, -_size,
		1.0f, 0.0f, 0.0f,

		// Top face
		-_size, _size, _size,
		0.0f, 1.0f, 0.0f,
		_size, _size, _size,
		0.0f, 1.0f, 0.0f,
		_size, _size, -_size,
		0.0f, 1.0f, 0.0f,
		-_size, _size, -_size,
		0.0f, 1.0f, 0.0f,
		-_size, _size, _size,
		0.0f, 1.0f, 0.0f,
		_size, _size, -_size,
		0.0f, 1.0f, 0.0f,
		// Bottom face
		-_size, -_size, _size,
		0.0f, -1.0f, 0.0f,
		_size, -_size, _size,
		0.0f, -1.0f, 0.0f,
		_size, -_size, -_size,
		0.0f, -1.0f, 0.0f,
		-_size, -_size, -_size,
		0.0f, -1.0f, 0.0f,
		-_size, -_size, _size,
		0.0f, -1.0f, 0.0f,
		_size, -_size, -_size,
		0.0f, -1.0f, 0.0f
	};

	setVertices(vertices);
}

void Cube::draw(const std::string& programName, ShaderManager& shaderManager, Camera& camera)
{
	updateMatrices();

	_vbo = std::move(VBO(_vertices));
	_vao = std::move(VAO(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr));
	Gl::VAO::vertexAttribPointer(1,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(float),
		reinterpret_cast<void*>(3 * sizeof(float)));

	if (!_vbo.isBind())
		_vbo.bind();
	if (!_vao.isBind())
		_vao.bind();

	GLint modelLoc = Gl::Program::getUniformLocation(shaderManager.getProgram(programName).getProgram(), "model");
	Gl::Program::uniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(camera.getModelMatrix()));

	GLint viewLoc = Gl::Program::getUniformLocation(shaderManager.getProgram(programName).getProgram(), "view");
	Gl::Program::uniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));

	GLint projLoc = Gl::Program::getUniformLocation(shaderManager.getProgram(programName).getProgram(), "projection");
	Gl::Program::uniformMatrix4fv(projLoc,
		1,
		GL_FALSE,
		glm::value_ptr(camera.getProjectionMatrix(
			(GLfloat)Window::instance().getSize().getX(),
			(GLfloat)Window::instance().getSize().getY())));
}
void Cube::draw(const std::string& programName, ShaderProgram* program, Camera& camera)
{
	updateMatrices();

	//ь_vbo = std::move(VBO(_vertices));
	//ь_vao = std::move(VAO(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr));
	//ьGl::VAO::vertexAttribPointer(1,
	//ь	3,
	//ь	GL_FLOAT,
	//ь	GL_FALSE,
	//ь	6 * sizeof(float),
	//ь	reinterpret_cast<void*>(3 * sizeof(float)));

//	if (!_vbo.isBind())
//		_vbo.bind();
//	if (!_vao.isBind())
//		_vao.bind();

	GLint modelLoc = Gl::Program::getUniformLocation(program->getProgram(), "model");
	Gl::Program::uniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(camera.getModelMatrix()));

	GLint viewLoc = Gl::Program::getUniformLocation(program->getProgram(), "view");
	Gl::Program::uniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));

	GLint projLoc = Gl::Program::getUniformLocation(program->getProgram(), "projection");
	Gl::Program::uniformMatrix4fv(projLoc,
		1,
		GL_FALSE,
		glm::value_ptr(camera.getProjectionMatrix(
			(GLfloat)Window::instance().getSize().getX(),
			(GLfloat)Window::instance().getSize().getY())));
}
