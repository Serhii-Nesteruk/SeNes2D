#include "../include/ShaderProgram.h"

#include "glm/gtc/type_ptr.hpp"

ShaderProgram::ShaderProgram(bool shouldCreate)
{
	if (shouldCreate)
		create();
}

ShaderProgram::ShaderProgram(GLuint vertShader, GLuint fragShader)
	: ShaderProgram(true)
{
	attachShader(vertShader);
	attachShader(fragShader);
	link();
}

ShaderProgram::~ShaderProgram()
{
	destroy();
}

void ShaderProgram::attachShader(GLuint shader)
{
	if (!isCreated())
		throw std::runtime_error("Shader program is not create");
	Gl::Program::attachShader(shader, _program);
	_isAttached = true;
	_isLinked = false;
}

void ShaderProgram::create()
{
	_program = Gl::Program::create();
}

void ShaderProgram::link()
{
	if (!isAttached())
		throw std::runtime_error("You can't to link the shader program, because the program is not attached");
	Gl::Program::link(_program);
	checkLinkStatus();

	_isLinked = true;
}

void ShaderProgram::use()
{
	if (!isLinked())
		throw std::runtime_error("You can't to use the shader program, because the program is not linked");

	Gl::Program::use(_program);
}

void ShaderProgram::destroy()
{
	if (isCreated())
		Gl::Program::deleteProgram(_program);
	_isAttached = false;
	_isLinked = false;
	_program = Gl::Program::invalidId;
}

bool ShaderProgram::isCreated() const
{
	return _program != Gl::Program::invalidId;
}

GLuint ShaderProgram::getProgram() const
{
	return _program;
}

GLint ShaderProgram::getProgramiv(GLenum pname)
{
	return Gl::Program::getProgramiv(_program, pname);
}

bool ShaderProgram::isAttached() const
{
	return _isAttached;
}

bool ShaderProgram::isLinked() const
{
	return _isLinked;
}

void ShaderProgram::uniform(const std::string& name, GLfloat v0)
{
	GLint location = Gl::Program::getUniformLocation(_program, name.data());
	Gl::Program::uniform1f(location, v0);
}

void ShaderProgram::uniform(const std::string& name, GLfloat v0, GLfloat v1)
{
	GLint location = Gl::Program::getUniformLocation(_program, name.data());
	Gl::Program::uniform2f(location, v0, v1);
}

void ShaderProgram::uniform(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2)
{
	GLint location = Gl::Program::getUniformLocation(_program, name.data());
	Gl::Program::uniform3f(location, v0, v1, v2);
}

void ShaderProgram::uniform(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	GLint location = Gl::Program::getUniformLocation(_program, name.data());
	Gl::Program::uniform4f(location, v0, v1, v2, v3);
}

void ShaderProgram::uniform(const std::string& name, GLint v0)
{
	GLint location = Gl::Program::getUniformLocation(_program, name.data());
	Gl::Program::uniform1i(location, v0);

}

void ShaderProgram::uniform(const std::string& name, GLint v0, GLint v1)
{
	GLint location = Gl::Program::getUniformLocation(_program, name.data());
	Gl::Program::uniform2i(location, v0, v1);
}

void ShaderProgram::uniform(const std::string& name, GLint v0, GLint v1, GLint v2)
{
	GLint location = Gl::Program::getUniformLocation(_program, name.data());
	Gl::Program::uniform3i(location, v0, v1, v2);
}

void ShaderProgram::uniform(const std::string& name, GLint v0, GLint v1, GLint v2, GLint v3)
{
	GLint location = Gl::Program::getUniformLocation(_program, name.data());
	Gl::Program::uniform4i(location, v0, v1, v2, v3);
}

void ShaderProgram::uniform(const std::string& name, GLuint v0)
{
	GLint location = Gl::Program::getUniformLocation(_program, name.data());
	Gl::Program::uniform1ui(location, v0);
}

void ShaderProgram::uniform(const std::string& name, GLuint v0, GLuint v1)
{
	GLint location = Gl::Program::getUniformLocation(_program, name.data());
	Gl::Program::uniform2ui(location, v0, v1);
}

void ShaderProgram::uniform(const std::string& name, GLuint v0, GLuint v1, GLuint v2)
{
	GLint location = Gl::Program::getUniformLocation(_program, name.data());
	Gl::Program::uniform3ui(location, v0, v1, v2);
}

void ShaderProgram::uniform(const std::string& name, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	GLint location = Gl::Program::getUniformLocation(_program, name.data());
	Gl::Program::uniform4ui(location, v0, v1, v2, v3);
}

void ShaderProgram::uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat2& value)
{
	GLint location = Gl::Program::getUniformLocation(_program, name.data());
	Gl::Program::uniformMatrix2fv(location, count, transponse, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat3& value)
{
	GLint location = Gl::Program::getUniformLocation(_program, name.data());
	Gl::Program::uniformMatrix3fv(location, count, transponse, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat4& value)
{
	GLint location = Gl::Program::getUniformLocation(_program, name.data());
	Gl::Program::uniformMatrix4fv(location, count, transponse, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat2x3& value)
{
	GLint location = Gl::Program::getUniformLocation(_program, name.data());
	Gl::Program::uniformMatrix2x3fv(location, count, transponse, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat3x2& value)
{
	GLint location = Gl::Program::getUniformLocation(_program, name.data());
	Gl::Program::uniformMatrix3x2fv(location, count, transponse, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat2x4& value)
{
	GLint location = Gl::Program::getUniformLocation(_program, name.data());
	Gl::Program::uniformMatrix2x4fv(location, count, transponse, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat4x2& value)
{
	GLint location = Gl::Program::getUniformLocation(_program, name.data());
	Gl::Program::uniformMatrix4x2fv(location, count, transponse, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat3x4& value)
{
	GLint location = Gl::Program::getUniformLocation(_program, name.data());
	Gl::Program::uniformMatrix3x4fv(location, count, transponse, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, GLsizei count, GLboolean transponse, const glm::mat4x3& value)
{
	GLint location = Gl::Program::getUniformLocation(_program, name.data());
	Gl::Program::uniformMatrix4x3fv(location, count, transponse, glm::value_ptr(value));
}

void ShaderProgram::checkLinkStatus()
{
	if (!getProgramiv(GL_LINK_STATUS))
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(_program, 512, NULL, infoLog);
		throw std::runtime_error("Can't to link the shader program");
	}
}

void ShaderProgram::dataReset(ShaderProgram& other)
{
	other._program = Gl::Program::invalidId;
	other._isAttached = false;
	other._isLinked = false;
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
{
	*this = std::move(other);
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other)
{
	if (this != &other)
	{
		// dataReset(*this);
		_program = other._program;
		_isAttached = other._isAttached;
		_isLinked = other._isLinked;
		dataReset(other);
	}

	return *this;
}

void ShaderProgram::uniform(const std::string& name, const glm::vec3& vec)
{
	uniform(name, vec.x, vec.y, vec.z);
}

void ShaderProgram::uniform(const std::string& name, const Color3& color)
{
	auto glColor = toGlColor3(color);
	uniform(name, glColor.r, glColor.g, glColor.b);
}
