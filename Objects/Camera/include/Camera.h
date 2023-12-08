#pragma once

#include "../../Wrappers/include/Gl.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

class Camera {
public:
    Camera(const glm::vec3& position, const glm::vec3& up, GLfloat& yaw, GLfloat pitch);
    ~Camera() = default;

    [[nodiscard]] glm::mat4 getViewMatrix() const;
    [[nodiscard]] glm::mat4 getProjectionMatrix(GLfloat screenWidth, GLfloat screenHeight) const;
    void processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true);
    void processKeyboard(int direction, GLfloat deltaTime);

    void setSpeed(GLfloat speed);
    void setSensitivity(GLfloat sensitivity);
    void setZoom(GLfloat zoom);
    void setNear(GLfloat near_);
    void setFar(GLfloat far_);
    void setYaw(GLfloat yaw);
    void setPitch(GLfloat pitch);

    [[nodiscard]] GLfloat getSpeed() const;
    [[nodiscard]] GLfloat getSensitivity() const;
    [[nodiscard]] GLfloat getZoom() const;
    [[nodiscard]] GLfloat getNear() const;
    [[nodiscard]] GLfloat getFar() const;
    [[nodiscard]] GLfloat getYaw() const;
    [[nodiscard]] GLfloat getPitch() const;

private:
    void updateCameraVectors();
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 worldUp;

    GLfloat yaw = 0.f;
    GLfloat pitch = 0.f;

    GLfloat speed = 5.f;
    GLfloat sensitivity = 0.1f;
    GLfloat zoom = 45.f;
    GLfloat near_ = 0.1f;
    GLfloat far_ = 100.f;
};