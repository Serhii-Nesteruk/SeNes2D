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

void SceneObject::draw(ShaderManager shaderManager, Camera& camera)
{
	updateMatrices();

	_vbo = std::move(VBO(_vertices));
	_vao = std::move(VAO(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr));

	if (!_vbo.isBind())
		_vbo.bind();
	if (!_vao.isBind())
		_vao.bind();

	//TODO: continue implementation...
}

void SceneObject::updateMatrices()
{
	if (_isReverseMatrixCalculating)
	{
		_modelMatrix = glm::translate(_modelMatrix, _position);
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotate.x), glm::vec3(1.f, 0.f, 0.f));
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotate.y), glm::vec3(0.f, 1.f, 0.f));
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotate.z), glm::vec3(0.f, 0.f, 1.f));

		_modelMatrix = glm::translate(_modelMatrix, -_origin);
		_modelMatrix = glm::translate(_modelMatrix, _origin);
		_modelMatrix = glm::scale(_modelMatrix, _scale);
		_modelMatrix = glm::translate(_modelMatrix, -_origin);
	}
	else
	{
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotate.x), glm::vec3(1.f, 0.f, 0.f));
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotate.y), glm::vec3(0.f, 1.f, 0.f));
		_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotate.z), glm::vec3(0.f, 0.f, 1.f));

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
	_rotate = rotate;
	updateMatrices();
}

glm::vec3 SceneObject::getRotate() const
{
	return _rotate
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