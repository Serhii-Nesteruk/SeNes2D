#include "Camera.h"

glm::mat4 Camera::getViewMatrix()
{
	glm::vec3 zAxis = -glm::normalize(getForwardVector());
	glm::vec3 xAxis = glm::normalize(glm::cross(getUpVector(), zAxis));
	glm::vec3 yAxis = glm::cross(zAxis, xAxis);

	glm::mat4 translation = glm::mat4(1.0f);
	translation[3][0] = -glm::dot(xAxis, _position);
	translation[3][1] = -glm::dot(yAxis, _position);
	translation[3][2] = glm::dot(zAxis, _position);

	glm::mat4 rotation = glm::mat4(1.0f);
	rotation[0] = glm::vec4(xAxis, 0.0f);
	rotation[1] = glm::vec4(yAxis, 0.0f);
	rotation[2] = glm::vec4(zAxis, 0.0f);

	return rotation * translation;
}

void Camera::processKeyboard(Movement direction, GLfloat deltaTime)
{
	GLfloat speed = _movementSpeed * deltaTime;
	switch (direction)
	{
	case Movement::FORWARD:
		_position += getForwardVector() * speed;
		break;
	case Movement::BACKWARD:
		_position -= getForwardVector() * speed;
		break;
	case Movement::LEFT:
		_position -= getRightVector() * speed;
		break;
	case Movement::RIGHT:
		_position += getRightVector() * speed;
		break;
	default:
		break;
	}
}
void Camera::processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch)
{
	xOffset *= _mouseSensitivity;
	yOffset *= _mouseSensitivity;

	_rotate.y += xOffset;
	_rotate.x += yOffset;

	if (constrainPitch)
	{
		if (_rotate.y >= 89.f)
			_rotate.y = 89.f;
		if (_rotate.x <= -89.f)
			_rotate.x = -89.f;
	}
}
void Camera::setSpeed(GLfloat speed)
{
	_movementSpeed = speed;
}
GLfloat Camera::getSpeed() const
{
	return _movementSpeed;
}
void Camera::setSensitivity(GLfloat sensitivity)
{
	_mouseSensitivity = sensitivity;
}
GLfloat Camera::getSensitivity() const
{
	return _mouseSensitivity;
}

Camera::Camera(const glm::vec3& position,
	GLfloat speed,
	GLfloat sensitivity)
	:  _movementSpeed(speed),
	  _mouseSensitivity(sensitivity)
{
	this->setPosition(position); // TODO: move it ^
}
glm::mat4 Camera::getProjectionMatrix(GLfloat windowWidth, GLfloat windowHeight) const
{
	return glm::perspective(glm::radians(90.f), windowWidth / windowHeight, 1.f, 10000.f); ;
}
