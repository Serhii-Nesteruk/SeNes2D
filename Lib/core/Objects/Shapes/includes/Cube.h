#pragma once

#include "SceneObject.h"

class Cube : public SceneObject
{
public:
	Cube();
	~Cube() = default;

	void setSize(GLfloat size);
	[[nodiscard]] GLfloat getSize() const;

	void setPosition(const glm::vec3& position) override;

	void draw(const std::string& programName, ShaderManager& shaderManager, Camera& camera) override;
	void draw(const std::string& programName,
		ShaderProgram* program, Camera& camera) override;
	void processKeyboard(Movement direction, GLfloat deltaTime) override {};
	virtual void processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch) override {}

private:
	void setupVertices();

private:
	GLfloat _size = 100.f;
};