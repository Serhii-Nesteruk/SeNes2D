#include "SceneObject.h"


void SceneObject::setPosition(const glm::vec3& position)
{
	_position = position;
}
glm::vec3 SceneObject::getPosition() const
{
	return _position;
}
void SceneObject::scale(const glm::vec3 scale)
{
	_scale = scale;
}
glm::vec3 SceneObject::getScaleVec() const
{
	return _scale;
}
void SceneObject::setTexture(const Texture& texture)
{
	_texture = texture;
}
Texture SceneObject::getTexture() const
{
	return _texture;
}
