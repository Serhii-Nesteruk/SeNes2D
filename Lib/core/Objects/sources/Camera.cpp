#include "Camera.h"

glm::mat4 Camera::getViewMatrix()
{
	return glm::mat4();
}
void Camera::processKeyboard(Movement direction, GLfloat deltaTime)
{
	GLfloat speed = _movementSpeed * deltaTime;
	switch (direction)
	{
	case Movement::FORWARD:
		_position += _front * speed;
		break;
	case Movement::BACKWARD:
		_position -= _front * speed;
		break;
	case Movement::LEFT:
		_position -= _right * speed;
		break;
	case Movement::RIGHT:
		_position += _right * speed;
		break;
	default:
		break;
	}
}
void Camera::processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch)
{
	xOffset *= _mouseSensitivity;
	yOffset *= _mouseSensitivity;

	_yaw += xOffset;
	_pitch += yOffset;

	if (constrainPitch)
	{
		if (_pitch >= 89.f)
			_pitch = 89.f;
		if (_pitch <= -89.f)
			_pitch = -89.f;
	}

	updateCameraVectors();
}
void Camera::updateCameraVectors()
{
	glm::vec3 tempFront{};
	tempFront.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	tempFront.y = sin(glm::radians(_pitch));
	tempFront.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_front = glm::normalize(tempFront);

	_right = glm::normalize(glm::cross(_front, _worldUp));
	_up = glm::normalize(glm::cross(_right, _front));
}
void Camera::setYaw(GLfloat yaw)
{
	_yaw = yaw;
	updateCameraVectors();
}
GLfloat Camera::getYaw() const
{
	return _yaw;
}
void Camera::setPitch(GLfloat pitch)
{
	_pitch = pitch;
	updateCameraVectors();
}
GLfloat Camera::getPitch() const
{
	return _pitch;
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
void Camera::setZoom(GLfloat zoom)
{
	_zoom = zoom;
}
GLfloat Camera::getZoom() const
{
	return _zoom;
}
