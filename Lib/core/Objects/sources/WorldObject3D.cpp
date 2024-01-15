#include "WorldObject3D.h"

WorldObject3D::WorldObject3D(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
	: _position(position), _rotation(rotation), _scale(scale)
{

}
WorldObject3D::WorldObject3D(const WorldObject3D& other)
{
	*this = other;
}
WorldObject3D& WorldObject3D::operator=(const WorldObject3D& other)
{
	copy(other);

	return *this;
}
WorldObject3D& WorldObject3D::operator=(WorldObject3D&& other)
{
	if (this != &other)
	{
		zeroingData(*this);
		copy(other);
		zeroingData(other);
	}
	return *this;
}

WorldObject3D::WorldObject3D(WorldObject3D&& other) noexcept
{
	*this = std::move(other);
}

void WorldObject3D::zeroingData(WorldObject3D& other)
{
	other._position = glm::vec3();
	other._rotation = glm::vec3();
	other._scale = glm::vec3();
}

void WorldObject3D::copy(const WorldObject3D& other)
{
	_position = other._position;
	_rotation = other._rotation;
	_scale = other._scale;
}

glm::vec3 WorldObject3D::getPosition() const
{
	return _position;
}

glm::vec3 WorldObject3D::getRotation() const
{
	return _rotation;
}

glm::vec3 WorldObject3D::getScale() const
{
	return _scale;
}

void WorldObject3D::setPosition(const glm::vec3& position)
{
	_position = position;
}

void WorldObject3D::setRotation(const glm::vec3& rotation)
{
	_rotation = rotation;
}

void WorldObject3D::setScale(const glm::vec3& scale)
{
	_scale = scale;
}
