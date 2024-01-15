#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class WorldObject3D
{
public:
	WorldObject3D() = default;
	WorldObject3D(const glm::vec3& position, const glm::vec3& rotation,
		const glm::vec3& scale);
	WorldObject3D(const WorldObject3D& other);
	WorldObject3D& operator=(const WorldObject3D& other);
	WorldObject3D(WorldObject3D&& other) noexcept;
	WorldObject3D& operator=(WorldObject3D&& other);
	virtual ~WorldObject3D()
	{
	};

	void copy(const WorldObject3D& other);

	[[nodiscard]] glm::vec3 getPosition() const;
	[[nodiscard]] glm::vec3 getRotation() const;
	[[nodiscard]] glm::vec3 getScale() const;

	void setPosition(const glm::vec3& position);
	void setRotation(const glm::vec3& rotation);
	void setScale(const glm::vec3& scale);

	virtual void draw() = 0;

private:
	void zeroingData(WorldObject3D& other);
protected:
	glm::vec3 _position;
	glm::vec3 _rotation;
	glm::vec3 _scale;
};