#pragma once

#include "VAO.h"
#include "VBO.h"
#include "Texture.h"
#include "ShaderManager.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera;

class SceneObject
{
public:
	SceneObject() = default;
	~SceneObject() = default;

	virtual void draw(ShaderManager shaderManager, Camera camera) = 0;

	void setTexture(const Texture& texture);
	[[nodiscard]] Texture getTexture() const;

	void setPosition(const glm::vec3& position);
	[[nodiscard]] glm::vec3 getPosition() const;

	void scale(const glm::vec3 scale);
	[[nodiscard]] glm::vec3 getScaleVec() const;

private:
	glm::vec3 _position{};
	glm::vec3 _scale{1.f, 1.f, 1.f};
	Texture _texture;
};