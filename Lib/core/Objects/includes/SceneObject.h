#pragma once

#include "VAO.h"
#include "VBO.h"
#include "Texture.h"
#include "ShaderManager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera;

// TODO: set up texture
class SceneObject
{
public:
	enum class Movement
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	SceneObject() = default;
	~SceneObject() = default;

	[[nodiscard]] virtual glm::vec3 getForwardVector() const;
	[[nodiscard]] virtual glm::vec3 getUpVector() const;
	[[nodiscard]] virtual glm::vec3 getRightVector() const;

	virtual void draw(ShaderManager shaderManager, Camera& camera);
	virtual void processKeyboard(Movement direction, GLfloat deltaTime) = 0;
	virtual void processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch) = 0;

	virtual void setTexture(const Texture& texture);
	[[nodiscard]] virtual const Texture* getTexture() const;

	virtual void setPosition(const glm::vec3& position);
	[[nodiscard]] virtual glm::vec3 getPosition() const;

	virtual void setScale(const glm::vec3& scale);
	[[nodiscard]] virtual glm::vec3 getScaleVec() const;

	void setReverseMatrixCalculating(bool value);
	[[nodiscard]] bool getReverseMatrixCalculating() const;

	[[nodiscard]] virtual glm::mat4 getModelMatrix() const;

	virtual void setRotate(const glm::vec3& rotate);
	[[nodiscard]] virtual glm::vec3 getRotate() const;
	virtual void setOrigin(const glm::vec3& origin);
	virtual void setVao(VAO&& vao);
	virtual void setVbo(VBO&& vbo);

	virtual void setVertices(const std::vector<GLfloat>& vertices);
	[[nodiscard]] virtual std::vector<GLfloat> getVertices() const;

protected:
	virtual void updateMatrices();

protected:
	bool _isReverseMatrixCalculating = false;
	glm::mat4 _modelMatrix = glm::mat4(1);
	glm::vec3 _rotate{};
	glm::vec3 _origin{};
	glm::vec3 _position{};
	glm::vec3 _scale{1.f, 1.f, 1.f};
	Texture* _texture = nullptr;
	VAO _vao;
	VBO _vbo;
	std::vector<GLfloat> _vertices{};
};