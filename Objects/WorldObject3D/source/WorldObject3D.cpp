#include "../include/WorldObject3D.h"

void WorldObject3D::render(ShaderProgram &shaderProgram, VAO &vao, Texture &texture1,
                           Texture &texture2) const { // TODO: improve it
    glm::mat4 modelMatrix = calculateModelMatrix();
    shaderProgram.uniform("uModelMatrix", 1, GL_FALSE, modelMatrix);

    vao.bind();

    texture1.active(GL_TEXTURE0);
    texture1.bind(Gl::Texture::Target::Texture2D);
    texture2.active(GL_TEXTURE1);
    texture2.bind(Gl::Texture::Target::Texture2D);

    Gl::drawArrays(GL_TRIANGLES, 0, 36); // TODO:
}

glm::mat4 WorldObject3D::calculateModelMatrix() const {
    glm::mat4 modelMatrix = glm::mat4(1.0);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-100, 0, 0));
    modelMatrix = glm::rotate(modelMatrix, glm::degrees(rotation.x), glm::vec3(1, 0, 0));
    modelMatrix = glm::rotate(modelMatrix, glm::degrees(rotation.y), glm::vec3(0, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, glm::degrees(rotation.z), glm::vec3(0, 0, 1));
    modelMatrix = glm::scale(modelMatrix, scale);
    return modelMatrix;
}

glm::vec3 WorldObject3D::getPosition() const {
    return position;
}

glm::vec3 WorldObject3D::getRotation() const {
    return rotation;
}

glm::vec3 WorldObject3D::getScale() const {
    return scale;
}

WorldObject3D::WorldObject3D(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &scale)
    :position(position), rotation(rotation), scale(scale) {

}

WorldObject3D::WorldObject3D(const WorldObject3D &other) {
    *this = other;
}

void WorldObject3D::update(ShaderProgram& shaderProgram) {
    glm::mat4 modelMatrix = calculateModelMatrix();
    shaderProgram.uniform("uModelMatrix", 1, GL_FALSE, modelMatrix);
}

WorldObject3D &WorldObject3D::operator=(const WorldObject3D &other) {
    this->position = other.position;
    this->rotation = other.rotation;
    this->scale = other.scale;

    return *this;
}

void WorldObject3D::setPosition(const glm::vec3 position_) {
    this->position = position_;
}

void WorldObject3D::setRotation(const glm::vec3 rotation) {
    this->rotation = rotation;
}

void WorldObject3D::setScale(const glm::vec3 scale) {
    this->scale = scale;
}

WorldObject3D::~WorldObject3D() {

}
