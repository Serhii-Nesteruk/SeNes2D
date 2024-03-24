#pragma once

#include "SceneObject.h"
#include "Color.h"

class Cube : public SceneObject
{
public:
	explicit Cube(bool isSetupVertices = true);
	~Cube() = default;

	void setSize(GLfloat size);
	[[nodiscard]] GLfloat getSize() const;

	void draw(const std::string& programName, ShaderManager& shaderManager, Camera& camera) override;
	void draw(const std::string& programName,
		ShaderProgram* program, Camera& camera) override;
	void processKeyboard(Movement direction, GLfloat deltaTime) override {};
	void processMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch) override {}

	void setColor(const Color3& rgb);
	[[nodiscard]] Color3 getColor() const;
private:
	void setupVertices();

private:
	GLfloat _size = 100.f;
	Color3 _rgb;
};