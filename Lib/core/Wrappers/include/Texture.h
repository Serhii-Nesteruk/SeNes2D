#pragma once

#include "Gl.h"

#include <filesystem>

class Texture {
public:
    using WrapMode = Gl::Texture::Wrap;
    using MagFilter = Gl::Texture::MagFilter;
    using MinFilter = Gl::Texture::MinFilter;
    using Target = Gl::Texture::Target;
    using Channel = Gl::Texture::Channel;

    Texture() = default;
    Texture(bool shouldGenerate, bool shouldBind);
    Texture(Target target, WrapMode wrapS, WrapMode wrapT, MinFilter min, MagFilter mag);
    Texture(const Texture& other);
    Texture& operator=(const Texture& other);
    ~Texture();

    void generate();
    void bind(Gl::Texture::Target target);
    void destroy();
    void active(GLenum texture_);

    void generateMipmap(Target target);

    void setWrapS(WrapMode wrapMode = WrapMode::None);
    void setWrapT(WrapMode wrapMode = WrapMode::None);
    void setWrapR(WrapMode wrapMode = WrapMode::None);

    void setMinAndMagFilter(MagFilter mag = MagFilter::None,
                            MinFilter min = MinFilter::None);
    void setMagFilter(MagFilter mag);
    void setMinFilter(MinFilter min);

    [[nodiscard]] bool isGenerated() const;
    [[nodiscard]] bool isBind() const;
    bool loadImage(const std::filesystem::path& path, bool shouldLoadToTheGraphicsCard = false);
    unsigned char* loadImageFromFile(const std::filesystem::path& path);

    void loadToTheGraphicsCard();

	void copy(const Texture& other);

private:
    unsigned char* _data = nullptr;
    GLint _width = 0, _height = 0, _nrChannels = 0;

    WrapMode _wrapS = WrapMode::None;
    WrapMode _wrapT = WrapMode::None;
    WrapMode _wrapR = WrapMode::None;

    bool _isBind = false;
    MagFilter _magFilter = MagFilter::None;
    MinFilter _minFilter = MinFilter::None;
    GLuint _texture = Gl::Texture::invalidId;
};