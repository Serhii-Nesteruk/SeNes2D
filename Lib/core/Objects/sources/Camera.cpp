#include "Camera.h"

glm::mat4 Camera::getViewMatrix()
{
	return _viewMatrix;
}

void Camera::updateViewMatrix()
{
	_viewMatrix = glm::mat4(1.0f);

	_viewMatrix = glm::rotate(_viewMatrix, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	_viewMatrix = glm::rotate(_viewMatrix, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	_viewMatrix = glm::translate(_viewMatrix, -_position);
}

void Camera::processKeyboard(Movement direction, GLfloat deltaTime)
{
	GLfloat speed = _movementSpeed * deltaTime;
	switch (direction)
	{
	case Movement::FORWARD:
		_position -= getForwardVector() * speed;
		break;
	case Movement::BACKWARD:
		_position += getForwardVector() * speed;
		break;
	case Movement::LEFT:
		_position -= getRightVector() * speed;
		break;
	case Movement::RIGHT:
		_position += getRightVector() * speed;
		break;
	case Movement::UP:
		_position -= getUpVector() * speed;
		break;
	case Movement::DOWN:
		_position += getUpVector() * speed;
		break;
	default:
		break;
	}
	updateViewMatrix();
}

void Camera::processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch)
{
	_xMouseOffset = xOffset;
	_yMouseOffset = yOffset;

	_xMouseOffset *= _mouseSensitivity;
	_yMouseOffset *= _mouseSensitivity;

	_rotation.y += _xMouseOffset;
	_rotation.x -= _yMouseOffset;

	//if (constrainPitch)
	//{
	//	if (_rotation.x > 89.f)
	//		_rotation.x = 89.f;
	//	if (_rotation.x < -89.f)
	//		_rotation.x = -89.f;
	//	if (_rotation.y > 89.f)
	//		_rotation.y = 89.f;
	//	if (_rotation.y < -89.f)
	//		_rotation.y = -89.f;
	//}

	updateViewMatrix();
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
	bool setCursorMousePosCallback,
	GLfloat speed,
	GLfloat sensitivity)
	:  _movementSpeed(speed),
	  _mouseSensitivity(sensitivity)
{
	this->setPosition(position); // TODO: move it ^

	if (setCursorMousePosCallback)
		setCursorPosCallback();
}

glm::mat4 Camera::getProjectionMatrix(GLfloat windowWidth, GLfloat windowHeight) const
{
	return glm::perspective(glm::radians(90.f), windowWidth / windowHeight, 1.f, 10000.f); ;
}

void Camera::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	static GLfloat lastX = 400, lastY = 300;
	_xMouseOffset = (GLfloat)xpos - lastX;
	_yMouseOffset = lastY - (GLfloat)ypos;
	lastX = (GLfloat)xpos;
	lastY = (GLfloat)ypos;
}

void Camera::setCursorPosCallback()
{
	glfwSetCursorPosCallback(Window::instance().getWinTarget(), mouseCallback);
}

void Camera::control(GLfloat deltaTime)
{
	processMouseMovement(_xMouseOffset, _yMouseOffset, true);
	if (GetAsyncKeyState('W') & 0x8000)
		processKeyboard(Camera::Movement::FORWARD, deltaTime);
	if (GetAsyncKeyState('S') & 0x8000)
		processKeyboard(Camera::Movement::BACKWARD, deltaTime);
	if (GetAsyncKeyState('D') & 0x8000)
		processKeyboard(Camera::Movement::RIGHT, deltaTime);
	if (GetAsyncKeyState('A') & 0x8000)
		processKeyboard(Camera::Movement::LEFT, deltaTime);
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		processKeyboard(Camera::Movement::UP, deltaTime);
	if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
		processKeyboard(Camera::Movement::DOWN, deltaTime);
}