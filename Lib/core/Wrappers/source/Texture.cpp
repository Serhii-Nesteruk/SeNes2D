#include "../include/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../../../dependencies/stb_image.h"

Texture::Texture(bool shouldGenerate, bool shouldBind) {
    if (shouldGenerate)
        generate();
    if(shouldBind)
        bind(Gl::Texture::Target::Texture2D);
}

Texture::~Texture() {
    destroy();
}

Texture::Texture(Texture::Target target, Texture::WrapMode wrapS, Texture::WrapMode wrapT,
                 Texture::MinFilter min, Texture::MagFilter mag)
                 : Texture(true, true) {
    setWrapS(WrapMode::Repeat);
    setWrapT(WrapMode::Repeat);
    setMinAndMagFilter(mag, min);
}

void Texture::generate() {
    Gl::Texture::generate(1, &_texture);
}

void Texture::bind(const Gl::Texture::Target target) {
    if (!isGenerated())
        DebugBreak(); // Texture is not generated

    Gl::Texture::bind(_texture, target);
    _isBind = true;
}

void Texture::generateMipmap(Texture::Target target) {
    Gl::Texture::generateMipmap(target);
}

bool Texture::isGenerated() const {
    return _texture != Gl::Texture::invalidId;
}

void Texture::setMinAndMagFilter(Texture::MagFilter mag, Texture::MinFilter min) {
    Gl::Texture::setMagFilter(mag); // TODO: raplace it
    Gl::Texture::setMinFilter(min);

    this->_magFilter = mag;
    this->_minFilter = min;
}

void Texture::setWrapS(Texture::WrapMode wrapMode) {
    Gl::Texture::setWrapS(wrapMode);
    this->_wrapS = wrapMode;
}

void Texture::setWrapT(Texture::WrapMode wrapMode) {
    Gl::Texture::setWrapS(wrapMode);
    this->_wrapT = wrapMode;
}

void Texture::setWrapR(Texture::WrapMode wrapMode) {
    Gl::Texture::setWrapS(wrapMode);
    this->_wrapR = wrapMode;
}

void Texture::destroy() {
    if (isGenerated()) {
        Gl::Texture::deleteTexture(1, &_texture);
        _isBind = false;
        _magFilter = MagFilter::None;
        _minFilter = MinFilter::None;
        _wrapS = WrapMode::None;
        _wrapT = WrapMode::None;
        _wrapR = WrapMode::None;
    }
}

void Texture::active(GLenum texture_) {
    Gl::Texture::activeTexture(texture_);
}

bool Texture::loadImage(const std::filesystem::path &path,
                        bool shouldLoadToTheGraphicsCard) {
    if (!isGenerated())
        DebugBreak(); //Texture is not generated
    if (!isBind())
        DebugBreak(); //Texture is not bind

    _data = loadImageFromFile(path);

    if (!_data)
        return false;

    if (shouldLoadToTheGraphicsCard)
        loadToTheGraphicsCard();

    return true;
}

bool Texture::isBind() const {
    return _isBind;
}

unsigned char* Texture::loadImageFromFile(const std::filesystem::path &path) {
    stbi_set_flip_vertically_on_load(true);
    return stbi_load(path.string().data(), &_width, &_height, &_nrChannels, 0);
}

void Texture::loadToTheGraphicsCard() {
    bind(Gl::Texture::Target::Texture2D);
    if (_data && isBind())
    {
        Gl::Texture::texImage2D(Target::Texture2D, 0, Channel::RGB, _width, _height,
                                0, Channel::RGB, GL_UNSIGNED_BYTE, _data);
        generateMipmap(Target::Texture2D);
    }
    else {
        DebugBreak(); //Failed to load texture
    }
    stbi_image_free(_data);
}

void Texture::setMagFilter(Texture::MagFilter mag) {
    Gl::Texture::setMagFilter(mag);
}

void Texture::setMinFilter(Texture::MinFilter min) {
    Gl::Texture::setMinFilter(min);
}

Texture::Texture(const Texture& other)
{
	*this = other;
}

Texture& Texture::operator=(const Texture& other)
{
	copy(other);

	return *this;
}

void Texture::copy(const Texture& other)
{
	_data = other._data;
	_width = other._width;
	_height = other._height;
	_nrChannels = other._nrChannels;
	_wrapS = other._wrapS;
	_wrapT = other._wrapT;
	_wrapR = other._wrapR;
	_isBind = other._isBind;
	_magFilter = other._magFilter;
	_minFilter = other._minFilter;
	_texture = other._texture;
}
