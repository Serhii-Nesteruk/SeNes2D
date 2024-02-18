#pragma once

#include "Gl.h"

#include "SceneObject.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera : public SceneObject
{
public:
	[[nodiscard]] glm::mat4 getViewMatrix();
	void processKeyboard(Movement direction, GLfloat deltaTime) override;
	void processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch) override;

	void setTexture(const Texture& texture) override = 0;
	void setYaw(GLfloat yaw);
	[[nodiscard]] GLfloat getYaw() const;
	void setPitch(GLfloat pitch);
	[[nodiscard]] GLfloat getPitch() const;
	void setSpeed(GLfloat speed);
	[[nodiscard]] GLfloat getSpeed() const;
	void setSensitivity(GLfloat sensitivity);
	[[nodiscard]] GLfloat getSensitivity() const;
	void setZoom(GLfloat zoom);
	[[nodiscard]] GLfloat getZoom() const;
private:
	void updateCameraVectors();
private:
	glm::mat4 _projection{};
	glm::vec3 _front{ };
	glm::vec3 _up{ };
	glm::vec3 _right{ };
	glm::vec3 _worldUp{ };

	GLfloat _yaw = -90.0f, _pitch = 0.f;
	GLfloat _movementSpeed = 25.0f, _mouseSensitivity = 0.1f, _zoom = 45.0f;
};
// class Camera
// {
// public:
// 	enum class CameraMovement
// 	{
// 		FORWARD,
// 		BACKWARD,
// 		LEFT,
// 		RIGHT
// 	};
//
// 	Camera() = default;
// 	Camera(const glm::vec3& position, const glm::vec3& up)
// 		: _position(position), _worldUp(up)
// 	{
// 		updateCameraVectors();
// 	}
// 	Camera(const glm::vec3& position, const glm::vec3& up, GLfloat yaw, GLfloat pitch)
// 		: _position(position), _up(up), _yaw(yaw), _pitch(pitch)
// 	{
// 		updateCameraVectors();
// 	}
// 	Camera(GLfloat posX,
// 		GLfloat posY,
// 		GLfloat posZ,
// 		GLfloat upX,
// 		GLfloat upY,
// 		GLfloat upZ,
// 		GLfloat yaw,
// 		GLfloat pitch,
// 		GLfloat sensitive,
// 		GLfloat movementSpeed,
// 		GLfloat zoom) : _position(posX, posY, posZ), _worldUp(upX, upY, upZ), _yaw(yaw), _pitch(pitch),
// 						_mouseSensitivity(sensitive),
// 						_movementSpeed(movementSpeed), _zoom(zoom)
// 	{
// 		updateCameraVectors();
// 	}
// 	~Camera() = default;
//
// 	[[nodiscard]] glm::mat4 getViewMatrix();
// 	void processKeyboard(CameraMovement direction, GLfloat deltaTime);
// 	void processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch);
//
// private:
// 	void updateCameraVectors();
//
// private:
// 	glm::vec3 _front{ };
// 	glm::vec3 _up{ };
// 	glm::vec3 _position{ };
// 	glm::vec3 _right{ };
// 	glm::vec3 _worldUp{ };
//
// 	GLfloat _yaw = -90.0f, _pitch = 0.f;
// 	GLfloat _movementSpeed = 25.0f, _mouseSensitivity = 0.1f, _zoom = 45.0f;
// };