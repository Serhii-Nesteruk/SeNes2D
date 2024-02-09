#include "../include/Shader.h"

#include "Utils.h"

Shader::Shader(const Gl::Shader::Type type_, bool shouldCreate)
{
	_type = type_;
	if (shouldCreate)
		create();
}

Shader::Shader(const std::filesystem::path& path, const Gl::Shader::Type type)
	: Shader(type, true)
{
	loadFromFile(path);
	compile();
}

Shader::~Shader()
{
	deleteShader();
}

void Shader::loadFromFile(const std::filesystem::path& path)
{
	const std::string source = Utils::getFileContent(path);
	setSource(source);
}

void Shader::compile()
{
	Gl::Shader::compile(_shader);

	checkCompileStatus();
	_isCompile = true;
}

void Shader::setSource(const std::string& source_)
{
	_source = source_;
	Gl::Shader::loadSource(_shader, _source.data());
}

void Shader::create()
{
	_shader = Gl::Shader::create(_type);
}

void Shader::deleteShader()
{
	//Gl::Shader::deleteShader(shader);
	glDeleteShader(_shader);
	_isCompile = false;
	_shader = Gl::Shader::invalidId;
	_source.clear();
}

const std::string& Shader::getSource() const
{
	return _source;
}

Gl::Shader::Type Shader::getType() const
{
	return _type;
}

GLuint Shader::getShader() const
{
	return _shader;
}

bool Shader::isCreate() const
{
	return _shader != Gl::Shader::invalidId;
}

bool Shader::isCompile() const
{
	return _isCompile;
}

void Shader::checkCompileStatus()
{
	if (!Gl::Shader::getShaderiv(_shader, GL_COMPILE_STATUS))
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(_shader, 512, NULL, infoLog);
		throw std::runtime_error("Failed to create shader");
	}
}

void Shader::setType(Gl::Shader::Type type_) {
    _type = type_; // TODO: update shader state
}
