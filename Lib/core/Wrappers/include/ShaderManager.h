#pragma once

#include "ShaderProgram.h"
#include "Shader.h"

#include <unordered_map>

class ShaderManager
{
public:
	struct ShaderPack
	{
	public:
		ShaderPack() = default;
		ShaderPack(Shader&& vert, Shader&& frag, ShaderProgram&& program);
		ShaderPack(const ShaderPack&) = delete;
		ShaderPack& operator=(const ShaderPack&) = delete;
		ShaderPack(ShaderPack&& other) noexcept;
		ShaderPack& operator=(ShaderPack&& other);
		~ShaderPack() = default;

		void setAll(Shader&& vert, Shader&& frag, ShaderProgram&& program);
		void setVert(Shader&& vert);
		void setFrag(Shader&& frag);
		void setProgram(ShaderProgram&& program);

		[[nodiscard]] Shader& getVert();
		[[nodiscard]] Shader& getFrag();
		[[nodiscard]] ShaderProgram& getProgram();

		void dataReset(ShaderPack& other);

	private:
		Shader _vert;
		Shader _frag;
		ShaderProgram _shaderProgram;
	};

	ShaderManager() = default;
	ShaderManager(const ShaderManager& other) = delete;
	ShaderManager& operator=(const ShaderManager& other) = delete;
	ShaderManager(ShaderManager&& other) noexcept;
	ShaderManager& operator=(ShaderManager&& other);

	[[nodiscard]] Shader& getVertShader(const std::string& name);
	[[nodiscard]] Shader& getFragShader(const std::string& name);
	[[nodiscard]] ShaderProgram& getProgram(const std::string& name);

	void add(const std::string& name , ShaderPack&& pack);
	void add(const std::string& name , Shader&& vert, Shader&& frag, ShaderProgram&& program);
	ShaderPack& get(const std::string& name);
	void clear();
	void erase(const std::string& name);

private:
	std::unordered_map<std::string, ShaderPack> _shaders;
};