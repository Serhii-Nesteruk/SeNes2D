#pragma once

#include "../../Wrappers/include/VAO.h"
#include "../../Wrappers/include/VBO.h"
#include "../../Wrappers/include/Texture.h"
#include "../../Wrappers/include/Shader.h"
#include "../../Wrappers/include/ShaderProgram.h"

#include "GLM/glm.hpp"
#include "../../dependencies/GLM/glm/gtx/transform.hpp"

class WorldObject3D {
public:
    WorldObject3D() = default;
    WorldObject3D(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
    WorldObject3D(const WorldObject3D& other);
    WorldObject3D& operator=(const WorldObject3D& other);
    virtual ~WorldObject3D();

    virtual void render(ShaderProgram& shaderProgram, VAO& vao, Texture& texture1, Texture& texture2) const;
    virtual void update(ShaderProgram& shaderProgram);

    [[nodiscard]] virtual glm::vec3 getPosition() const;

    [[nodiscard]] virtual glm::vec3 getRotation() const;
    [[nodiscard]] virtual glm::vec3 getScale() const;

    virtual void setPosition(const glm::vec3 position_);
    virtual void setRotation(const glm::vec3 rotation);
    virtual void setScale(const glm::vec3 scale);

private:
    [[nodiscard]] virtual glm::mat4 calculateModelMatrix() const;

private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};