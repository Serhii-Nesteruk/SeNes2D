#include "../include/VBO.h"

VBO::VBO(bool isGenerate, bool isBind)
{
	if (isGenerate)
		generate();
	if (isBind && isGenerated())
		bind();
}

VBO::VBO(const std::vector<GLfloat>& data, GLenum usage) : VBO(true, true)
{
	setData(data, usage);
}

VBO::~VBO()
{
	destroy();
}

void VBO::generate()
{
	if (!isGenerated()) {
		Gl::VBO::generate(1, &_id);
		if (!isGenerated())
			throw std::runtime_error("Can't to generate VBO");
	}
}

void VBO::bind()
{
	Gl::VBO::bind(GL_ARRAY_BUFFER, _id);
	_isBind = true;
}

void VBO::unbind()
{
	Gl::VBO::unbind(GL_ARRAY_BUFFER);
	_isBind = false;
}

void VBO::destroy()
{
	if (isGenerated())
		//glDeleteBuffers(1, &id);
		Gl::VBO::deleteBuffers(1, &_id);
	_id = Gl::VBO::invalidId;
	_isBind = false;
}

void VBO::setData(const std::vector<GLfloat>& data, GLenum usage)
{
	if (!isBind())
		throw std::runtime_error("VBO is not bind");
	if (!isGenerated())
		throw std::runtime_error("VBO is not generate");
	Gl::VBO::buffData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), data.data(), usage);
}

bool VBO::isBind() const
{
	return _isBind;
}

bool VBO::isGenerated() const
{
	return _id != Gl::VBO::invalidId;
}

GLuint VBO::getId() const
{
	return _id;
}

VBO::VBO(VBO&& other) noexcept
{
	*this = std::move(other);
}
VBO& VBO::operator=(VBO&& other) noexcept
{
	if (this != &other)
	{
		_isBind = other._isBind;
		_id = other._id;
	}
	return *this;
}
