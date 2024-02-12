#include "ShaderManager.h"

void ShaderManager::ShaderPack::setVert(Shader&& vert)
{
	_vert = std::move(vert);
}

void ShaderManager::ShaderPack::setFrag(Shader&& frag)
{
	_frag = std::move(frag);
}

void ShaderManager::ShaderPack::setProgram(ShaderProgram&& program)
{
	_shaderProgram = std::move(program);
}

void ShaderManager::ShaderPack::setAll(Shader&& vert, Shader&& frag, ShaderProgram&& program)
{
	setVert(std::move(vert));
	setFrag(std::move(frag));
	setProgram(std::move(program));
}

Shader& ShaderManager::ShaderPack::getVert()
{
	return _vert;
}

Shader& ShaderManager::ShaderPack::getFrag()
{
	return _frag;
}

ShaderProgram& ShaderManager::ShaderPack::getProgram()
{
	return _shaderProgram;
}
ShaderManager::ShaderPack::ShaderPack(ShaderManager::ShaderPack&& other) noexcept
{
	*this = std::move(other);
}
ShaderManager::ShaderPack::ShaderPack(Shader&& vert, Shader&& frag, ShaderProgram&& program)
{

}
ShaderManager::ShaderPack& ShaderManager::ShaderPack::operator=(ShaderManager::ShaderPack&& other)
{
	setVert(std::move(other._vert));
	setFrag(std::move(other._frag));
	setProgram(std::move(other._shaderProgram));
	return *this;
}
void ShaderManager::ShaderPack::dataReset(ShaderManager::ShaderPack& other)
{
	other = std::move(ShaderPack());
}

Shader& ShaderManager::getVertShader(const std::string& name)
{
	auto it = _shaders.find(name);
	if (it != _shaders.end())
	{
		return it->second.getVert();
	}
	else
	{
		throw std::runtime_error("Vertex shader '" + name + "' not found in shader manager");
	}
}

Shader& ShaderManager::getFragShader(const std::string& name)
{
	auto it = _shaders.find(name);
	if (it != _shaders.end())
	{
		return it->second.getFrag();
	}
	else
	{
		throw std::runtime_error("Vertex shader '" + name + "' not found in shader manager");
	}
}

ShaderProgram& ShaderManager::getProgram(const std::string& name)
{
	auto it = _shaders.find(name);
	if (it != _shaders.end())
		return it->second.getProgram();
	throw std::runtime_error("Vertex shader '" + name + "' not found in shader manager");
}

void ShaderManager::add(const std::string& name, ShaderManager::ShaderPack&& pack)
{
	_shaders[name] = std::move(pack);
}

void ShaderManager::add(const std::string& name, Shader&& vert, Shader&& frag, ShaderProgram&& program)
{
	_shaders[name] = ShaderPack(std::move(vert), std::move(frag), std::move(program));
}

ShaderManager::ShaderPack& ShaderManager::get(const std::string& name)
{
	auto it = _shaders.find(name);
	if (it != _shaders.end())
		return it->second;
	throw std::runtime_error("The " + name + " shader pack not found");
}

ShaderManager::ShaderManager(ShaderManager&& other) noexcept
{
	*this = std::move(other);
}

ShaderManager& ShaderManager::operator=(ShaderManager&& other)
{
	if (this != &other)
	{
		clear();
		for (auto it = other._shaders.begin(); it != other._shaders.end(); ++it)
			_shaders[it->first] = std::move(it->second);
	}
	return *this;
}
void ShaderManager::clear()
{
	_shaders.clear();
}
void ShaderManager::erase(const std::string& name)
{
	_shaders.erase(name);
}
