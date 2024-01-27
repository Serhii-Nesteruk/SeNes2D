#pragma once

#include "VAO.h"
#include "VBO.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "WorldObject3D.h"

#include <vector>

class Cube : public WorldObject3D
{
public:
	Cube(const Texture& texture, const glm::vec3& position, const glm::vec3& rotation,
		const glm::vec3& scale);
	Cube(const Texture& texture, const glm::vec3& position, const glm::vec3& rotation,
		const glm::vec3& scale, GLfloat sideLength);
	~Cube() override
	{
	};

	void setVertexAndFragmentShaders(const Shader& vertexShader, const Shader& fragmentShader);
	void setVertexShader(const Shader& vertexShader);
	void setFragmentShader(const Shader& fragmentShader);
	void setupShaderProgram();

	void setSideLength(GLfloat sideLength);
	[[nodiscard]] GLfloat getSideLength() const;

	void draw() override;

private:
	void generateVertices();
	void setupVAOAndVBO();

private:
	GLfloat _sideLength{ };
	std::vector<GLfloat> _vertices{};
	VAO _vao;
	VBO _vbo;
	ShaderProgram _shaderProgram;
	Texture _texture;
	Shader _vertexShader;
	Shader _fragmentShader;
};