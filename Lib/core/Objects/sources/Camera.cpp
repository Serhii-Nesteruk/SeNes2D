#include "Camera.h"

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(_position, _position + _front, _up);
}
void Camera::processKeyboard(Camera::CameraMovement direction, GLfloat deltaTime)
{
	GLfloat speed = _movementSpeed * deltaTime;
	switch (direction)
	{
	case CameraMovement::FORWARD:
		_position += _front * speed;
		break;
	case CameraMovement::BACKWARD:
		_position -= _front * speed;
		break;
	case CameraMovement::LEFT:
		_position -= _right * speed;
		break;
	case CameraMovement::RIGHT:
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