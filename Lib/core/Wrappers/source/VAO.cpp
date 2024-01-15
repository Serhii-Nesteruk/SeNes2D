#include "../include/VAO.h"

VAO::VAO(bool isGenerate, bool isBind)
{
	if (isGenerate)
	{
		generate();
	}
	if (isBind && isGenerated())
	{
		bind();
	}
}

VAO::VAO(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) : VAO(true, true)
{
	vertexAttribPointer(index, size, type, normalized, stride, pointer);
}

VAO::~VAO()
{
	destroy();
}

void VAO::generate()
{
	if (!isGenerated()) {
		Gl::VAO::generate(1, &_id);
		if (!isGenerated())
			throw std::runtime_error("Can't to generate VAO");
	}
}

void VAO::bind()
{
	Gl::VAO::bind(_id);
	_isBind = true;
}

void VAO::unbind()
{
	Gl::VAO::unbind();
	_isBind = false;
}

void VAO::destroy()
{
	if (isGenerated())
		glDeleteVertexArrays(1, &_id);
		//Gl::VAO::deleteVertexArrays(1, &id);

	_id = Gl::VAO::invalidId;
	_isBind = false;
}

bool VAO::isGenerated() const
{
	return _id != Gl::VAO::invalidId;
}

bool VAO::isBind() const
{
	return _isBind;
}

GLuint VAO::getId() const
{
	return _id;
}

void VAO::vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normilized,
	GLsizei stride, const void* pointer)
{
	Gl::VAO::vertexAttribPointer(index, size, type, normilized, stride, pointer);
}

VAO& VAO::operator=(const VAO& other)
{
	_isBind = other._isBind;
	_id = other._id;

	return *this;
}

VAO::VAO(const VAO& other)
{
	*this = other;
}
