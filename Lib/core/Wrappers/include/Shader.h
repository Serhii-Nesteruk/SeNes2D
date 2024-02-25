#pragma once

#include "Gl.h"

#include <string>
#include <filesystem>

class Shader {
public:
	Shader() = default;
	explicit Shader(const Gl::Shader::Type& type, bool shouldCreate = true);
	Shader(const std::filesystem::path& path, const Gl::Shader::Type& type);
	Shader(const Shader& other) = delete;
	Shader& operator=(const Shader& other) = delete;
	Shader(Shader&& other) noexcept;
	Shader& operator=(Shader&& other);
	~Shader();

	void loadFromFile(const std::filesystem::path& path);
	void compile();
	void setSource(const std::string& source_);
	void create();
	void deleteShader();

	void setType(Gl::Shader::Type type_);

	[[nodiscard]] const std::string& getSource() const;
	[[nodiscard]] Gl::Shader::Type getType() const;

	[[nodiscard]] GLuint getShader() const;

	[[nodiscard]] bool isCreate() const;
	[[nodiscard]] bool isCompile() const;

private:
	void checkCompileStatus();
	void dataReset(Shader& shader);

private:
	bool _isCompile = false;
	GLuint _shader = Gl::Shader::invalidId;
	Gl::Shader::Type _type = Gl::Shader::Type::FRAGMENT;
	std::string _source{};
		
};