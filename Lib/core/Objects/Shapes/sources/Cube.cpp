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
		_position.x, _position.y, _position.z,
		0.0f, 0.0f, 1.0f,
		_position.x + _size, _position.y, _position.z,
		0.0f, 0.0f, 1.0f,
		_position.x + _size, _position.y + _size, _position.z,
		0.0f, 0.0f, 1.0f,
		_position.x, _position.y, _position.z,
		0.0f, 0.0f, 1.0f,
		_position.x, _position.y + _size, _position.z,
		0.0f, 0.0f, 1.0f,
		_position.x + _size, _position.y + _size, _position.z,
		0.0f, 0.0f, 1.0f,

		// Back face
		_position.x, _position.y, _position.z + _size,
		0.0f, 0.0f, -1.0f,
		_position.x, _position.y + _size, _position.z + _size,
		0.0f, 0.0f, -1.0f,
		_position.x + _size, _position.y + _size, _position.z + _size,
		0.0f, 0.0f, -1.0f,
		_position.x, _position.y, _position.z + _size,
		0.0f, 0.0f, -1.0f,
		_position.x + _size, _position.y, _position.z + _size,
		0.0f, 0.0f, -1.0f,
		_position.x + _size, _position.y + _size, _position.z + _size,
		0.0f, 0.0f, -1.0f,

		// Left face
		_position.x, _position.y, _position.z,
		-1.0f, 0.0f, 0.0f,
		_position.x, _position.y + _size, _position.z,
		-1.0f, 0.0f, 0.0f,
		_position.x, _position.y + _size, _position.z + _size,
		-1.0f, 0.0f, 0.0f,
		_position.x, _position.y, _position.z,
		-1.0f, 0.0f, 0.0f,
		_position.x, _position.y, _position.z + _size,
		-1.0f, 0.0f, 0.0f,
		_position.x, _position.y + _size, _position.z + _size,
		-1.0f, 0.0f, 0.0f,

		// Right face
		_position.x + _size, _position.y, _position.z,
		1.0f, 0.0f, 0.0f,
		_position.x + _size, _position.y + _size, _position.z,
		1.0f, 0.0f, 0.0f,
		_position.x + _size, _position.y + _size, _position.z + _size,
		1.0f, 0.0f, 0.0f,
		_position.x + _size, _position.y, _position.z,
		1.0f, 0.0f, 0.0f,
		_position.x + _size, _position.y, _position.z + _size,
		1.0f, 0.0f, 0.0f,
		_position.x + _size, _position.y + _size, _position.z + _size,
		1.0f, 0.0f, 0.0f,

		// Top face
		_position.x, _position.y + _size, _position.z,
		0.0f, 1.0f, 0.0f,
		_position.x, _position.y + _size, _position.z + _size,
		0.0f, 1.0f, 0.0f,
		_position.x + _size, _position.y + _size, _position.z + _size,
		0.0f, 1.0f, 0.0f,
		_position.x, _position.y + _size, _position.z,
		0.0f, 1.0f, 0.0f,
		_position.x + _size, _position.y + _size, _position.z,
		0.0f, 1.0f, 0.0f,
		_position.x + _size, _position.y + _size, _position.z + _size,
		0.0f, 1.0f, 0.0f,
		// Bottom face
		_position.x, _position.y, _position.z,
		0.0f, -1.0f, 0.0f,
		_position.x, _position.y, _position.z + _size,
		0.0f, -1.0f, 0.0f,
		_position.x + _size, _position.y, _position.z + _size,
		0.0f, -1.0f, 0.0f,
		_position.x, _position.y, _position.z,
		0.0f, -1.0f, 0.0f,
		_position.x + _size, _position.y, _position.z,
		0.0f, -1.0f, 0.0f,
		_position.x + _size, _position.y, _position.z + _size,
		0.0f, -1.0f, 0.0f
	};


	setVertices(vertices);

	_vbo.generate();
	_vao.generate();

	_vbo.bind();
	_vao.bind();

	_vbo.setData(_vertices);
	_vao.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	_vao.vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));

	_vao.bind();
	_vbo.bind();
}

void Cube::draw(const std::string& programName, ShaderManager& shaderManager, Camera& camera)
{
}

void Cube::draw(const std::string& programName, ShaderProgram* program, Camera& camera)
{
	updateMatrices();

	program->uniform("model", 1, GL_FALSE, _modelMatrix);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cube::setPosition(const glm::vec3& position)
{
	SceneObject::setPosition(position);
	setupVertices();
}
