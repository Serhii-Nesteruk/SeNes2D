#pragma once

#include "Gl.h"

class VAO {
public:
	VAO() = default;
	VAO(bool isGenerate, bool isBind);
	VAO(const VAO& other) = delete;
	VAO& operator=(const VAO& other) = delete;
	VAO(VAO&& other) noexcept;
	VAO& operator=(VAO&& other) noexcept;

	VAO(GLuint index, GLint size, GLenum type, GLboolean normilized,
		GLsizei stride, const void* pointer);
	~VAO();

	void generate();
	void bind();
	void unbind();
	void destroy();

	void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normilized,
		GLsizei stride, const void* pointer);

	[[nodiscard]] bool isBind() const;
	[[nodiscard]] bool isGenerated() const;

	[[nodiscard]] GLuint getId() const;

private:
	bool _isBind = false;
	GLuint _id = Gl::VAO::invalidId;
};