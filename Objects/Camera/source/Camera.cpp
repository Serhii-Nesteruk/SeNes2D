#include "../include/Camera.h"

Camera::Camera(const glm::vec3 &position, const glm::vec3 &up, GLfloat &yaw, GLfloat pitch)
    : position(position), up(up), yaw(yaw), pitch(pitch) {
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix(GLfloat screenWidth, GLfloat screenHeight) const {
    return glm::perspective(glm::radians(zoom), screenWidth / screenHeight, near_, far_);
}

void Camera::updateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch) {
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (constrainPitch) {
        if (pitch > 89.0f) // TODO: replace magic numbers
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::processKeyboard(GLint direction, GLfloat deltaTime) {
    GLfloat velocity = speed * deltaTime;
    if (direction == GLFW_KEY_W)
        position += front * velocity;
    if (direction == GLFW_KEY_S)
        position -= front * velocity;
    if (direction == GLFW_KEY_A)
        position -= right * velocity;
    if (direction == GLFW_KEY_D)
        position += right * velocity;
    updateCameraVectors();
}

void Camera::setSpeed(GLfloat speed) {
    this->speed = speed;
    updateCameraVectors();
}

void Camera::setSensitivity(GLfloat sensitivity) {
    this->sensitivity = sensitivity;
    updateCameraVectors();
}

void Camera::setZoom(GLfloat zoom) {
    this->zoom = zoom;
    updateCameraVectors();
}

void Camera::setNear(GLfloat near_) {
    this->near_ = near_;
    updateCameraVectors();
}

void Camera::setFar(GLfloat far_) {
    this->far_ = far_;
    updateCameraVectors();
}

void Camera::setYaw(GLfloat yaw) {
    this->yaw = yaw;
    updateCameraVectors();
}

void Camera::setPitch(GLfloat pitch) {
    this->pitch = pitch;
    updateCameraVectors();
}

GLfloat Camera::getSpeed() const {
    return this->speed;
}

GLfloat Camera::getSensitivity() const {
    return this->sensitivity;
}

GLfloat Camera::getZoom() const {
    return this->zoom;
}

GLfloat Camera::getNear() const {
    return this->near_;
}

GLfloat Camera::getFar() const {
    return this->far_;
}

GLfloat Camera::getYaw() const {
    return this->yaw;
}

GLfloat Camera::getPitch() const {
    return this->pitch;
}