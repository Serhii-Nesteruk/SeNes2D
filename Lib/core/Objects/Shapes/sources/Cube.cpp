#include "Cube.h"

#include "Camera.h"

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

	_vbo.generate();
	_vao.generate();

	_vbo.bind();
	_vao.bind();

	_vbo.setData(_vertices);
	_vao.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	_vao.vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
}

void Cube::draw(const std::string& programName, ShaderManager& shaderManager, Camera& camera)
{
}

void Cube::draw(const std::string& programName, ShaderProgram* program, Camera& camera) // TODO: programName
{
	updateMatrices();

	program->uniform("model", 1, GL_FALSE, _modelMatrix);
	program->uniform("uDefaultColor", _rgb);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

Cube::Cube(bool isSetupVertices /* = true */)
{
	if (isSetupVertices)
	{
		setupVertices();
	}
}

void Cube::setColor(const Color3& rgb)
{
	_rgb = rgb;
}

Color3 Cube::getColor() const
{
	return _rgb;
}
