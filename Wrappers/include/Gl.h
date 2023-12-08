#pragma once

#include "../GLAD/glad.h"
#include "../../../Utils/include/Utils.h"
#include "../glfw-3.3.7/include/GLFW/glfw3.h"
//#include <GL/glew.h>

#include <string>
#include <vector>

// clang-format off
#include <Windows.h>
#include <debugapi.h>
// clang-format on

class Gl {
public:
    Gl() = delete;

    static void checkGLErrors() noexcept(true)
    {
        switch (glGetError())
        {
            case GL_INVALID_ENUM:
                DebugBreak(); // ("Set when an enumeration parameter is not legal");
            case GL_INVALID_VALUE:
                DebugBreak(); // ("Set when a value parameter is not legal");
            case GL_INVALID_OPERATION:
                DebugBreak(); // ("Set when the state for a command is not legal for its given parameters");
            case GL_STACK_OVERFLOW:
                DebugBreak(); // ("Set when a stack pushing operation causes a stack overflow");
            case GL_STACK_UNDERFLOW:
                DebugBreak(); // ("Set when a stack popping operation occurs while the stack is at its lowest point");
            case GL_OUT_OF_MEMORY:
                DebugBreak(); // ("Set when a memory allocation operation cannot allocate (enough) memory");
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                DebugBreak(); // ("Set when reading or writing to a framebuffer that is not complete");
        }
    }

    class VBO {
    public:
        inline static const GLuint invalidId = GL_INVALID_INDEX;

        static void generate(GLsizei n, GLuint* arrays);
        static void bind(GLenum target, GLuint buffer);
        static void unbind(GLenum target);
        static bool isBind();
        static void buffData(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
        static void deleteBuffers(GLsizei n, GLuint* arrays);

    private:
        inline static GLuint id = invalidId;
        friend class Gl;
    };

    class VAO {
    public:
        inline static const GLuint invalidId = GL_INVALID_INDEX;

        static void generate(GLsizei n, GLuint* arrays);
        static void bind(GLuint array);
        static void unbind();
        static bool isBind();
        static void enableVertexAttribArray(GLuint index);
        static void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized,
                                        GLsizei stride, const void* pointer);
        static void disableVertexAttribArray(GLuint index);
        static void deleteVertexArrays(GLsizei n, GLuint* arrays);

    private:
        inline static GLuint id = invalidId;
        friend class Gl;
    };


    class Shader {
    public:
        inline static const GLuint invalidId = GL_INVALID_INDEX;

        enum class Type {
            VERTEX = GL_VERTEX_SHADER,
            FRAGMENT = GL_FRAGMENT_SHADER,
            GEOMETRY = GL_GEOMETRY_SHADER
        };

        [[nodiscard]] static GLuint createAndLoadFromFile(const std::filesystem::path& path, const Type type);
        [[nodiscard]] static GLuint create(const Type type);
        [[nodiscard]] static GLint getShaderiv(GLuint shader, GLenum pname);
        static void deleteShader(GLuint shader);
        static void compile(GLuint shader);
        static void loadSource(GLuint shader, const char* shaderSource);
    private:
        inline static GLuint id = invalidId;
        friend class Gl;
    };

    class Texture {
    public:
        inline static const GLuint invalidId = GL_INVALID_INDEX;

        enum class Target
        {
            None,
            Texture2D = GL_TEXTURE_2D,
            CubeMapPositiveX = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
            CubeMapNegativeX = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
            CubeMapPositiveY = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
            CubeMapNegativeY = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
            CubeMapPositiveZ = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
            CubeMapNegativeZ = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
            CubeMap = GL_TEXTURE_CUBE_MAP
        };

        enum class MagFilter
        {
            None,
            Linear = GL_LINEAR,
            Nearest = GL_NEAREST,
        };

        enum class MinFilter
        {
            None,
            Linear = GL_LINEAR,
            Nearest = GL_NEAREST,
            NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
            LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
            NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
            LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR
        };

        enum class Wrap
        {
            None,
            Clamp2Edge = GL_CLAMP_TO_EDGE,
            Clamp2Border = GL_CLAMP_TO_BORDER,
            MirroredRepeat = GL_MIRRORED_REPEAT,
            Repeat = GL_REPEAT,
            MirrorClamp2Edge = GL_MIRROR_CLAMP_TO_EDGE
        };

        enum class Channel
        {
            SRGB = GL_SRGB,
            RGB = GL_RGB,
            RGBA = GL_RGBA,
            SRGBA = GL_SRGB_ALPHA
        };

        static void generate(GLsizei n, GLuint* textures);
        static void bind(GLuint texture, Target target = Target::Texture2D);
        static void setWrapS(Wrap param, Target target = Target::Texture2D);
        static void setWrapT(Wrap param, Target target = Target::Texture2D);
        static void setWrapR(Wrap param, Target target = Target::Texture2D);
        static void setMinFilter(MinFilter param, Target target = Target::Texture2D);
        static void setMagFilter(MagFilter param, Target target = Target::Texture2D);
        static void texImage2D(Target target, GLint level, Channel internalFormat,
                               GLsizei width, GLsizei height, GLint border, Channel format,
                               GLenum type, const void* pixels);
        static void generateMipmap(Target target = Target::Texture2D);
        static void deleteTexture(GLsizei n, GLuint* texture);
        static void activeTexture(GLenum texture);

    private:
        inline static GLuint id = invalidId;
    };

    class Program {
    public:
        inline static const GLuint invalidId = GL_INVALID_INDEX;

        [[nodiscard]] static GLuint create();
        static void attachShader(GLuint shader, GLuint shaderProgram);
        static void link(GLuint shaderProgram);
        [[nodiscard]] static bool isAttached();
        static void deleteProgram(GLuint shaderProgram);
        static void use(GLuint shaderProgram);
        [[nodiscard]] static GLint getProgramiv(GLuint shaderProgram, GLenum pname);
        [[nodiscard]] static GLint getUniformLocation(GLuint program, const GLchar* name);

        static void uniform1f(GLint location, GLfloat v0);
        static void uniform2f(GLint location, GLfloat v0, GLfloat v1);
        static void uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
        static void uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
        static void uniform1i(GLint location, GLint v0);
        static void uniform2i(GLint location, GLint v0, GLint v1);
        static void uniform3i(GLint location, GLint v0, GLint v1, GLint v2);
        static void uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
        static void uniform1ui(GLint location, GLuint v0);
        static void uniform2ui(GLint location, GLuint v0, GLuint v1);
        static void uniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2);
        static void uniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
        static void uniform1fv(GLint location, GLsizei count, const GLfloat* value);
        static void uniform2fv(GLint location, GLsizei count, const GLfloat* value);
        static void uniform3fv(GLint location, GLsizei count, const GLfloat* value);
        static void uniform4fv(GLint location, GLsizei count, const GLfloat* value);
        static void uniform1iv(GLint location, GLsizei count, const GLint* value);
        static void uniform2iv(GLint location, GLsizei count, const GLint* value);
        static void uniform3iv(GLint location, GLsizei count, const GLint* value);
        static void uniform4iv(GLint location, GLsizei count, const GLint* value);
        static void uniform1uiv(GLint location, GLsizei count, const GLuint* value);
        static void uniform2uiv(GLint location, GLsizei count, const GLuint* value);
        static void uniform3uiv(GLint location, GLsizei count, const GLuint* value);
        static void uniform4uiv(GLint location, GLsizei count, const GLuint* value);
        static void uniformMatrix2fv(GLint location, GLsizei count, GLboolean transponse, const GLfloat* value);
        static void uniformMatrix3fv(GLint location, GLsizei count, GLboolean transponse, const GLfloat* value);
        static void uniformMatrix4fv(GLint location, GLsizei count, GLboolean transponse, const GLfloat* value);
        static void uniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transponse, const GLfloat* value);
        static void uniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transponse, const GLfloat* value);
        static void uniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transponse, const GLfloat* value);
        static void uniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transponse, const GLfloat* value);
        static void uniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transponse, const GLfloat* value);
        static void uniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transponse, const GLfloat* value);

    private:
        inline static GLuint id = invalidId;
    };

    static void viewport(GLint x, GLint y, GLsizei width, GLsizei height);
    static void drawArrays(GLenum mode, GLint first,GLsizei count);
};