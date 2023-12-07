#include "../include/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

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
    Gl::Texture::generate(1, &texture);
}

void Texture::bind(const Gl::Texture::Target target) {
    if (!isGenerated())
        DebugBreak(); // Texture is not generated

    Gl::Texture::bind(texture, target);
    isBind_ = true;
}

void Texture::generateMipmap(Texture::Target target) {
    Gl::Texture::generateMipmap(target);
}

bool Texture::isGenerated() const {
    return texture != Gl::Texture::invalidId;
}

void Texture::setMinAndMagFilter(Texture::MagFilter mag, Texture::MinFilter min) {
    Gl::Texture::setMagFilter(mag); // TODO: raplace it
    Gl::Texture::setMinFilter(min);

    this->magFilter = mag;
    this->minFilter = min;
}

void Texture::setWrapS(Texture::WrapMode wrapMode) {
    Gl::Texture::setWrapS(wrapMode);
    this->wrapS = wrapMode;
}

void Texture::setWrapT(Texture::WrapMode wrapMode) {
    Gl::Texture::setWrapS(wrapMode);
    this->wrapT = wrapMode;
}

void Texture::setWrapR(Texture::WrapMode wrapMode) {
    Gl::Texture::setWrapS(wrapMode);
    this->wrapR = wrapMode;
}

void Texture::destroy() {
    if (isGenerated()) {
        Gl::Texture::deleteTexture(1, &texture);
        isBind_ = false;
        magFilter = MagFilter::None;
        minFilter = MinFilter::None;
        wrapS = WrapMode::None;
        wrapT = WrapMode::None;
        wrapR = WrapMode::None;
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

    data = loadImageFromFile(path);

    if (!data)
        return false;

    if (shouldLoadToTheGraphicsCard)
        loadToTheGraphicsCard();

    return true;
}

bool Texture::isBind() const {
    return isBind_;
}

unsigned char* Texture::loadImageFromFile(const std::filesystem::path &path) {
    stbi_set_flip_vertically_on_load(true);
    return stbi_load(path.string().data(), &width, &height, &nrChannels, 0);
}

void Texture::loadToTheGraphicsCard() {
    bind(Gl::Texture::Target::Texture2D);
    if (data)
    {
        Gl::Texture::texImage2D(Target::Texture2D, 0, Channel::RGB, width, height,
                                0, Channel::RGB, GL_UNSIGNED_BYTE, data);
        generateMipmap(Target::Texture2D);
    }
    else {
        DebugBreak(); //Failed to load texture
    }
    stbi_image_free(data);
}

void Texture::setMagFilter(Texture::MagFilter mag) {
    Gl::Texture::setMagFilter(mag);
}

void Texture::setMinFilter(Texture::MinFilter min) {
    Gl::Texture::setMinFilter(min);
}
