#pragma once

#include "../../Objects/WorldObject3D/include/WorldObject3D.h"

#include <vector>

class Cube : public WorldObject3D {
public:
    Cube() = default;
    Cube(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3 scale);

    void initializeVertices();
    void initializeVertices(const std::vector<GLfloat>& vertices);

    void initVAOAndVBO();
    void draw(ShaderProgram& shaderProgram, Texture& texture1, Texture& texture2);
private:
    VAO vao;
    VBO vbo;
    std::vector<GLfloat> vertices {};
};
