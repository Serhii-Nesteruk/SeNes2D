#include "../include/Camera.h"

Camera::Camera(const glm::vec3 &position, const glm::vec3 &up, GLfloat &yaw, GLfloat pitch)
    : position(position), up(up), yaw(yaw), pitch(pitch) {
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix(GLfloat screenWidth, GLfloat screenHeight) const {
    glm::mat4 view = glm::mat4(1.f);
    view = glm::translate(view, position * glm::vec3(1.f, 1.f, -1.f));
    view = glm::rotate(view, glm::radians(pitch), glm::vec3(1.f, 0.f, 0.f));
    view = glm::rotate(view, glm::radians(yaw), glm::vec3(0.f, 1.f, 0.f));
    glm::mat4 projection = glm::perspective(glm::radians(zoom), screenWidth / screenHeight, near_ ,far_);
    return projection * glm::inverse(view);
}

void Camera::updateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(pitch)) * -sin(glm::radians(yaw));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front = glm::normalize(newFront);

    glm::vec3 newUp;
    float newPitch = pitch + glm::radians(-90.f);

    newUp.x = cos(glm::radians(newPitch)) * -sin(glm::radians(yaw));
    newUp.y = sin(glm::radians(newPitch));
    newUp.z = cos(glm::radians(newPitch)) * cos(glm::radians(yaw));
    up = newUp;

    right = glm::normalize(glm::cross(front, up));
}

void Camera::processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch) {
    if (xOffset == 0.f && yOffset == 0.f)
        return;

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

    while (yaw >= 360.f)
        yaw -= 360.f;
    while (yaw < 0.f)
        yaw += 360.f;

    // updateCameraVectors();
}

void Camera::processKeyboard(GLint direction, GLfloat deltaTime) {
    GLfloat velocity = speed * deltaTime * 10.f;
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

glm::vec3 Camera::getPosition() const {
    return position;
}