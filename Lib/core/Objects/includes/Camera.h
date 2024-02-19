#pragma once

#include "Gl.h"

#include "SceneObject.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera : public SceneObject
{
public:
	Camera() = default;
	Camera(const glm::vec3& position,
		 GLfloat speed = 35.f, GLfloat sensitivity = 0.1f);
	Camera(const Camera&) = default;
	Camera& operator=(const Camera&) = default;
	Camera(Camera&&) = default;
	Camera& operator=(Camera&&) = default;
	~Camera() = default;

	[[nodiscard]] glm::mat4 getViewMatrix();
	void processKeyboard(Movement direction, GLfloat deltaTime) override;
	void processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch) override;

	void setTexture(const Texture& texture) override {};
	void setSpeed(GLfloat speed);
	[[nodiscard]] GLfloat getSpeed() const;
	void setSensitivity(GLfloat sensitivity);
	[[nodiscard]] GLfloat getSensitivity() const;
	[[nodiscard]] glm::mat4 getProjectionMatrix(GLfloat windowWidth, GLfloat windowHeight) const;

private:
	glm::mat4 _projection{};

	GLfloat _movementSpeed = 25.f, _mouseSensitivity = 0.1f;
};