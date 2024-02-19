#include "Cube.h"
//
//Cube::Cube(const Texture& texture, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
//	: WorldObject3D(position, rotation, scale), _texture(texture)
//{
//	setupVAOAndVBO();
//}
//
//Cube::Cube(const Texture& texture, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale,
//	GLfloat sideLength) : WorldObject3D(position, rotation, scale), _sideLength(sideLength), _texture(texture)
//{
//	setupVAOAndVBO();
//}
//
//void Cube::setSideLength(GLfloat sideLength)
//{
//	_sideLength = sideLength;
//	generateVertices();
//}
//
//GLfloat Cube::getSideLength() const
//{
//	return _sideLength;
//}
//
//void Cube::generateVertices()
//{
//	GLfloat halfSide = _sideLength / 2.0f;
//
//	_vertices =
//	{
//		// Front face
//		-halfSide, -halfSide, halfSide,
//		halfSide, -halfSide, halfSide,
//		halfSide, halfSide, halfSide,
//		-halfSide, halfSide, halfSide,
//
//		// Back face
//		-halfSide, -halfSide, -halfSide,
//		halfSide, -halfSide, -halfSide,
//		halfSide, halfSide, -halfSide,
//		-halfSide, halfSide, -halfSide,
//
//		// Left face
//		-halfSide, -halfSide, -halfSide,
//		-halfSide, -halfSide, halfSide,
//		-halfSide, halfSide, halfSide,
//		-halfSide, halfSide, -halfSide,
//
//		// Right face
//		halfSide, -halfSide, -halfSide,
//		halfSide, -halfSide, halfSide,
//		halfSide, halfSide, halfSide,
//		halfSide, halfSide, -halfSide,
//
//		// Top face
//		-halfSide, halfSide, -halfSide,
//		halfSide, halfSide, -halfSide,
//		halfSide, halfSide, halfSide,
//		-halfSide, halfSide, halfSide,
//
//		// Bottom face
//		-halfSide, -halfSide, -halfSide,
//		halfSide, -halfSide, -halfSide,
//		halfSide, -halfSide, halfSide,
//		-halfSide, -halfSide, halfSide
//	};
//
//	for (GLuint i = 0; i < _vertices.size(); i += 3) {
//		_vertices.at(i) += _position.x	;
//		_vertices.at(i + 1) += _position.y;
//		_vertices.at(i + 2) += _position.z;
//	}
//}
//
//void Cube::draw()
//{
//	if (!_shaderProgram.isLinked())
//	{
//		DebugBreak(); // The Shader was not linked
//	}
//
//	_shaderProgram.use();
//	_vao.bind();
//	Gl::drawArrays(GL_TRIANGLES, 0, 24); // TODO: magic number
//}
//
//void Cube::setupVAOAndVBO()
//{
//	VAO tempVao(true, true);
//	VBO tempVbo(_vertices);
//
//	tempVao.vertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), nullptr);
//	tempVao.vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
//	tempVao.vertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), reinterpret_cast<void*>(5 * sizeof(float)));
//
//	tempVao.unbind();
//	tempVbo.unbind();
//
//	_vao = std::move(tempVao);
//	_vbo = std::move(tempVbo);
//}
//
//void Cube::setFragmentShader(const Shader& fragmentShader)
//{
//	_fragmentShader = std::move(fragmentShader);
//}
//
//void Cube::setVertexShader(const Shader& vertexShader)
//{
//	_vertexShader = vertexShader;
//}
//
//void Cube::setVertexAndFragmentShaders(const Shader& vertexShader, const Shader& fragmentShader)
//{
//	setVertexShader(vertexShader);
//	setFragmentShader(fragmentShader);
//	setupShaderProgram();
//}
//
//void Cube::setupShaderProgram()
//{
//	_shaderProgram.attachShader(_vertexShader.getShader());
//	_shaderProgram.attachShader(_fragmentShader.getShader());
//	_shaderProgram.link();
//}
