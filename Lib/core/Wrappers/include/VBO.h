#pragma once

#include "Gl.h"

#include <vector>

class VBO {
public:
	VBO() = default;
	VBO(const VBO& other) = delete;
	VBO& operator=(const VBO& other) = delete;
	VBO(VBO&& other) noexcept;
	VBO& operator=(VBO&& other) noexcept;

	VBO(bool isGenerate, bool isBind);
	explicit VBO(const std::vector<GLfloat>& data, GLenum usage = GL_STATIC_DRAW);
	~VBO();

	void generate();
	void bind();
	void unbind();
	void destroy();
	void setData(const std::vector<GLfloat>& data, GLenum usage = GL_STATIC_DRAW);

	[[nodiscard]] bool isBind() const;
	[[nodiscard]] bool isGenerated() const;

	[[nodiscard]] GLuint getId() const;
private:
	bool _isBind = false;
	GLuint _id = Gl::VBO::invalidId;
};