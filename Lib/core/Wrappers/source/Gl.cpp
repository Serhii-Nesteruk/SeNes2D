#include "../include/Gl.h"

#include <iostream>

void Gl::VBO::generate(GLsizei n, GLuint* arrays)
{
    glGenBuffers(n, arrays);
    checkGLErrors();
}

void Gl::VBO::bind(GLenum target, GLuint buffer)
{
    glBindBuffer(target, buffer);
    id = buffer;
    checkGLErrors();
}

void Gl::VBO::unbind(GLenum target)
{
    glBindBuffer(target, 0u);
    id = invalidId;
    checkGLErrors();
}

bool Gl::VBO::isBind()
{
    return id != invalidId;
}

void Gl::VBO::buffData(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
{
    if (!isBind())
        throw std::runtime_error("VBO is not bound");
    glBufferData(target, size, data, usage);
    checkGLErrors();
}

void Gl::VBO::deleteBuffers(GLsizei n, GLuint* arrays)
{
    glDeleteBuffers(n, arrays);
    id = invalidId;
    checkGLErrors();
}

void Gl::VAO::generate(GLsizei n, GLuint* arrays)
{
    glGenVertexArrays(n, arrays);
    checkGLErrors();
}

void Gl::VAO::bind(GLuint array)
{
    glBindVertexArray(array);
    id = array;
    checkGLErrors();
}

void Gl::VAO::unbind()
{
    glBindVertexArray(0);
    id = invalidId;
    checkGLErrors();
}

bool Gl::VAO::isBind()
{
    return id != invalidId;
}

void Gl::VAO::enableVertexAttribArray(GLuint index)
{
    if (!isBind())
        throw std::exception("VAO is not bound");

    glEnableVertexAttribArray(index);
    checkGLErrors();
}

void Gl::VAO::vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized,
                                  GLsizei stride, const void* pointer)
{
    if (!isBind())
        throw std::exception("VAO is not bound");

    enableVertexAttribArray(index);
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    checkGLErrors();
}

void Gl::VAO::disableVertexAttribArray(GLuint index)
{
    if (!isBind())
        throw std::exception("VAO is not bound");
    glDisableVertexAttribArray(index);
    checkGLErrors();
}

void Gl::VAO::deleteVertexArrays(GLsizei n, GLuint* arrays)
{
    glDeleteVertexArrays(n, arrays);
    id = invalidId;
    checkGLErrors();
}

void Gl::viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
    glViewport(x, y, width, height);
    checkGLErrors();
}

void Gl::drawArrays(GLenum mode, GLint first, GLsizei count)
{
    if (!Gl::VAO::isBind())
        throw std::exception("VAO is not bind");
    else
        glDrawArrays(mode, first, count);
    checkGLErrors();
}

GLuint Gl::Shader::createAndLoadFromFile(const std::filesystem::path& path, const Type type)
{
    const std::string fileContent = Utils::getFileContent(path);
    GLuint shader = create(type);
    loadSource(shader, fileContent.data());
    compile(shader);
    return shader;
}

GLuint Gl::Shader::create(const Type type)
{
    GLuint shader = glCreateShader(static_cast<GLenum>(type));
    checkGLErrors();

    return shader;
}

GLint Gl::Shader::getShaderiv(GLuint shader, GLenum pname)
{
    GLint params = 0;
    glGetShaderiv(shader, pname, &params);

    checkGLErrors();

    return params;
}

void Gl::Shader::deleteShader(GLuint shader)
{
    glDeleteShader(shader);
    checkGLErrors();
    id = invalidId;
}

void Gl::Shader::compile(GLuint shader)
{
    glCompileShader(shader);
    checkGLErrors();
}

void Gl::Shader::loadSource(GLuint shader, const char* shaderSource)
{
    glShaderSource(shader, 1,&shaderSource, nullptr);
    checkGLErrors();
    id = shader;
}

GLuint Gl::Program::create()
{
    GLuint shaderProgram = glCreateProgram();
    checkGLErrors();
    return shaderProgram;
}

void Gl::Program::attachShader(GLuint shader, GLuint shaderProgram)
{
    glAttachShader(shaderProgram, shader);
    checkGLErrors();
    id = shaderProgram;
}

void Gl::Program::link(GLuint shaderProgram)
{
    if (!isAttached())
        std::cerr << "Shader program is not attached";
    else
        glLinkProgram(shaderProgram);
    checkGLErrors();
}

bool Gl::Program::isAttached()
{
    return id != invalidId;
}

void Gl::Program::deleteProgram(GLuint shaderProgram)
{
    glDeleteProgram(shaderProgram);
    id = invalidId;
    checkGLErrors();
}

void Gl::Program::use(GLuint shaderProgram)
{
    if (!isAttached())
        throw std::runtime_error("Shader program is not attached");
    glUseProgram(shaderProgram);
    checkGLErrors();
    id = shaderProgram;
}

GLint Gl::Program::getProgramiv(GLuint shaderProgram, GLenum pname)
{
    GLint params = 0;
    glGetProgramiv(shaderProgram, pname, &params);

    checkGLErrors();

    return params;
}

GLint Gl::Program::getUniformLocation(GLuint program, const GLchar* name)//TODO: check return value for -1
{
	GLint location = 0;

	if (auto foundProgram = uniformCache.find(program); foundProgram == uniformCache.end())
	{
		uniformCache[program] = {};
	}

	auto& foundProgram = uniformCache.find(program)->second;
	auto uniformIt = foundProgram.find(std::string(name));
	if (uniformIt == foundProgram.end())
	{
		location = glGetUniformLocation(program, name);
		foundProgram[std::string(name)] = location;
	}
	else
	{
		location = uniformIt->second;
	}

    checkGLErrors();
    return location;
}

void Gl::Program::uniform1f(GLint location, GLfloat v0)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform1f(location, v0);
    checkGLErrors();
}

void Gl::Program::uniform2f(GLint location, GLfloat v0, GLfloat v1)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform2f(location, v0, v1);
    checkGLErrors();
}

void Gl::Program::uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform3f(location, v0, v1, v2);
    checkGLErrors();
}

void Gl::Program::uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform4f(location, v0, v1, v2, v3);
    checkGLErrors();
}

void Gl::Program::uniform1i(GLint location, GLint v0)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform1i(location, v0);
    checkGLErrors();
}

void Gl::Program::uniform2i(GLint location, GLint v0, GLint v1)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform2i(location, v0, v1);
    checkGLErrors();
}

void Gl::Program::uniform3i(GLint location, GLint v0, GLint v1, GLint v2)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform3i(location, v0, v1, v2);
    checkGLErrors();
}

void Gl::Program::uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform4i(location, v0, v1, v2, v3);
    checkGLErrors();
}

void Gl::Program::uniform1ui(GLint location, GLuint v0)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform1ui(location, v0);
    checkGLErrors();
}

void Gl::Program::uniform2ui(GLint location, GLuint v0, GLuint v1)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform2ui(location, v0, v1);
    checkGLErrors();
}

void Gl::Program::uniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform3ui(location, v0, v1, v2);
    checkGLErrors();
}

void Gl::Program::uniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform4ui(location, v0, v1, v2, v3);
    checkGLErrors();
}

void Gl::Program::uniform1fv(GLint location, GLsizei count, const GLfloat* value)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform1fv(location, count, value);
    checkGLErrors();
}

void Gl::Program::uniform2fv(GLint location, GLsizei count, const GLfloat* value)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform2fv(location, count, value);
    checkGLErrors();
}

void Gl::Program::uniform3fv(GLint location, GLsizei count, const GLfloat* value)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform3fv(location, count, value);
    checkGLErrors();
}

void Gl::Program::uniform4fv(GLint location, GLsizei count, const GLfloat* value)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform4fv(location, count, value);
    checkGLErrors();
}

void Gl::Program::uniform1iv(GLint location, GLsizei count, const GLint* value)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform1iv(location, count, value);
    checkGLErrors();
}

void Gl::Program::uniform2iv(GLint location, GLsizei count, const GLint* value)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform2iv(location, count, value);
    checkGLErrors();
}

void Gl::Program::uniform3iv(GLint location, GLsizei count, const GLint* value)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform3iv(location, count, value);
    checkGLErrors();
}

void Gl::Program::uniform4iv(GLint location, GLsizei count, const GLint* value)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform4iv(location, count, value);
    checkGLErrors();
}

void Gl::Program::uniform1uiv(GLint location, GLsizei count, const GLuint* value)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform1uiv(location, count, value);
    checkGLErrors();
}

void Gl::Program::uniform2uiv(GLint location, GLsizei count, const GLuint* value)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform2uiv(location, count, value);
    checkGLErrors();
}

void Gl::Program::uniform3uiv(GLint location, GLsizei count, const GLuint* value)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform3uiv(location, count, value);
    checkGLErrors();
}

void Gl::Program::uniform4uiv(GLint location, GLsizei count, const GLuint* value)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniform4uiv(location, count, value);
    checkGLErrors();
}

void Gl::Program::uniformMatrix2fv(GLint location, GLsizei count, GLboolean transponse, const GLfloat* value)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniformMatrix2fv(location, count, transponse, value);
    checkGLErrors();
}

void Gl::Program::uniformMatrix3fv(GLint location, GLsizei count, GLboolean transponse, const GLfloat* value)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniformMatrix3fv(location, count, transponse, value);
    checkGLErrors();
}

void Gl::Program::uniformMatrix4fv(GLint location, GLsizei count, GLboolean transponse, const GLfloat* value)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniformMatrix4fv(location, count, transponse, value);
    checkGLErrors();
}

void Gl::Program::uniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transponse, const GLfloat* value)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniformMatrix2x3fv(location, count, transponse, value);
    checkGLErrors();
}

void Gl::Program::uniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transponse, const GLfloat* value)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniformMatrix3x2fv(location, count, transponse, value);
    checkGLErrors();
}

void Gl::Program::uniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transponse, const GLfloat* value)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniformMatrix2x4fv(location, count, transponse, value);
    checkGLErrors();
}

void Gl::Program::uniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transponse, const GLfloat* value)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniformMatrix4x2fv(location, count, transponse, value);
    checkGLErrors();
}

void Gl::Program::uniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transponse, const GLfloat* value)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniformMatrix3x4fv(location, count, transponse, value);
    checkGLErrors();
}

void Gl::Program::uniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transponse, const GLfloat* value)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set uniform without using the shader program");

    glUniformMatrix4x3fv(location, count, transponse, value);
    checkGLErrors();
}

void Gl::Texture::generate(GLsizei n, GLuint* textures)
{
    glGenTextures(n, textures);
    checkGLErrors();
}

void Gl::Texture::bind(GLuint texture, Target target)
{
    id = texture;
    glBindTexture(static_cast<GLenum>(target), texture);
    checkGLErrors();
}

void Gl::Texture::setWrapS(Wrap param, Target target)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set WrapS without binding texture");

    glTexParameteri(static_cast<GLenum>(target), GL_TEXTURE_WRAP_S,
                    static_cast<GLint>(param));
    checkGLErrors();
}

void Gl::Texture::setWrapT(Wrap param, Target target)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set WrapT without binding texture");

    glTexParameteri(static_cast<GLenum>(target), GL_TEXTURE_WRAP_T,
                    static_cast<GLint>(param));
    checkGLErrors();
}

void Gl::Texture::setWrapR(Wrap param, Target target)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set WrapR without binding texture");

    glTexParameteri(static_cast<GLenum>(target), GL_TEXTURE_WRAP_R,
                    static_cast<GLint>(param));
    checkGLErrors();
}

void Gl::Texture::setMinFilter(MinFilter param, Target target)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set min filter without binding texture");

    glTexParameteri(static_cast<GLenum>(target), GL_TEXTURE_MIN_FILTER,
                    static_cast<GLint>(param));
    checkGLErrors();
}

void Gl::Texture::setMagFilter(MagFilter param, Target target)
{
    if (id == invalidId)
        throw std::runtime_error("You can't set min filter without binding texture");

    glTexParameteri(static_cast<GLenum>(target), GL_TEXTURE_MIN_FILTER,
                    static_cast<GLint>(param));
    checkGLErrors();
}

void Gl::Texture::texImage2D(Target target, GLint level, Channel internalFormat, GLsizei width, GLsizei height, GLint border, Channel format, GLenum type, const void* pixels)
{
    if (id == invalidId)
        throw std::runtime_error("Texture are not bound !!!");

    glTexImage2D(static_cast<GLenum>(target), level, static_cast<GLint>(internalFormat),
                 width, height, border, static_cast<GLenum>(format), type, pixels);
    checkGLErrors();
}

void Gl::Texture::generateMipmap(Target target)
{
    if (id == invalidId)
        throw std::runtime_error("Texture are not bound !!!");

    glGenerateMipmap(static_cast<GLenum>(target));
    checkGLErrors();
}

void Gl::Texture::deleteTexture(GLsizei n, GLuint* texture)
{
    id = invalidId;
    glDeleteTextures(n, texture);
    checkGLErrors();
}

void Gl::Texture::activeTexture(GLenum texture)
{
    glActiveTexture(texture);
    checkGLErrors();
}
