#include "SceneObject.h"

void SceneObject::setPosition(const glm::vec3& position)
{
	_position = position;
	updateMatrices();
}

glm::vec3 SceneObject::getPosition() const
{
	return _position;
}

void SceneObject::setScale(const glm::vec3& scale)
{
	_scale = scale;
	updateMatrices();
}

glm::vec3 SceneObject::getScaleVec() const
{
	return _scale;
}

void SceneObject::setTexture(const Texture& texture)
{
	*_texture = texture;
}

const Texture* SceneObject::getTexture() const
{
	return _texture;
}

void SceneObject::draw(const std::string& programName, ShaderManager& shaderManager, Camera& camera)
{
// updateMatrices();

// _vbo = std::move(VBO(_vertices));
// _vao = std::move(VAO(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr));
// Gl::VAO::vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));

// if (!_vbo.isBind())
// 	_vbo.bind();
// if (!_vao.isBind())
// 	_vao.bind();

// GLint modelLoc = glGetUniformLocation(shaderManager.getProgram(programName).getProgram(), "model");
// glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(camera.getModelMatrix())); // *

}

void SceneObject::updateMatrices()
{
	if (_isReverseMatrixCalculating)
	{
		_modelMatrix = glm::translate(_modelMatrix, _position);
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.x), glm::vec3(1.f, 0.f, 0.f));
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.y), glm::vec3(0.f, 1.f, 0.f));
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.z), glm::vec3(0.f, 0.f, 1.f));

		_modelMatrix = glm::translate(_modelMatrix, -_origin);
		_modelMatrix = glm::translate(_modelMatrix, _origin);
		_modelMatrix = glm::scale(_modelMatrix, _scale);
		_modelMatrix = glm::translate(_modelMatrix, -_origin);
	}
	else
	{
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.x), glm::vec3(1.f, 0.f, 0.f));
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.y), glm::vec3(0.f, 1.f, 0.f));
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.z), glm::vec3(0.f, 0.f, 1.f));

		_modelMatrix = glm::translate(_modelMatrix, _position);
		_modelMatrix = glm::translate(_modelMatrix, _origin);
		_modelMatrix = glm::scale(_modelMatrix, _scale);
	}
}

void SceneObject::setOrigin(const glm::vec3& origin)
{
	_origin = origin;
	updateMatrices();
}

void SceneObject::setReverseMatrixCalculating(bool value)
{
	_isReverseMatrixCalculating = value;
}

bool SceneObject::getReverseMatrixCalculating() const
{
	return _isReverseMatrixCalculating;
}

glm::mat4 SceneObject::getModelMatrix() const
{
	return _modelMatrix;
}

void SceneObject::setRotate(const glm::vec3& rotate)
{
	_rotation = rotate;
	updateMatrices();
}

glm::vec3 SceneObject::getRotate() const
{
	return _rotation;
}

void SceneObject::setVao(VAO&& vao)
{
	_vao = std::move(vao);
}

void SceneObject::setVbo(VBO&& vbo)
{
	_vbo = std::move(vbo);
}

void SceneObject::setVertices(const std::vector<GLfloat>& vertices)
{
	_vertices = vertices;
}

std::vector<GLfloat> SceneObject::getVertices() const
{
	return _vertices;
}
glm::vec3 SceneObject::getForwardVector() const //*
{
	auto r = glm::vec2(glm::radians(_rotation.x), glm::radians(_rotation.y));

	// clang-format off
	return glm::normalize(glm::vec3{
		cos(r.x) * -sin(r.y),
		sin(r.x),
		cos(r.x) * cos(r.y)
	});
	// clang-format on
}

glm::vec3 SceneObject::getUpVector() const //*
{
	auto r = glm::vec2(glm::radians(_rotation.x), glm::radians(_rotation.y));
	r.x += glm::radians(-90.f);

	// clang-format off
	return glm::normalize(glm::vec3{
		cos(r.x) * -sin(r.y),
		sin(r.x),
		cos(r.x) * cos(r.y)
	});
	// clang-format on
}

glm::vec3 SceneObject::getRightVector() const //*
{
	return glm::normalize(glm::cross(getForwardVector(), getUpVector()));
}
