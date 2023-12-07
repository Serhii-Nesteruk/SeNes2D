#include "Wrappers/include/VAO.h"
#include "Wrappers/include/VBO.h"
#include "Wrappers/include/Texture.h"
#include "Wrappers/include/Shader.h"
#include "Wrappers/include/ShaderProgram.h"
#include "Wrappers/include/Window.h"

#include "GLM/glm.hpp"
#include "dependencies/GLM/glm/gtx/transform.hpp"

#include <iostream>

void rotateControl(Window& window, float& rotateX, float& rotateY, float& rotateZ)
{
    if (glfwGetKey(window.getWinTarget(), GLFW_KEY_D) == GLFW_PRESS)
        rotateX += 0.0001f;

    if (glfwGetKey(window.getWinTarget(), GLFW_KEY_A) == GLFW_PRESS)
        rotateX -= 0.0001f;

    if (glfwGetKey(window.getWinTarget(), GLFW_KEY_W) == GLFW_PRESS)
        rotateY -= 0.0001f;

    if (glfwGetKey(window.getWinTarget(), GLFW_KEY_S) == GLFW_PRESS)
        rotateY += 0.0001f;

    if (glfwGetKey(window.getWinTarget(), GLFW_KEY_Q) == GLFW_PRESS)
        rotateZ -= 0.0001f;

    if (glfwGetKey(window.getWinTarget(), GLFW_KEY_E) == GLFW_PRESS)
        rotateZ += 0.0001f;
}

int main() {
    Window window(Window::Size(600, 600), "Window");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Can't init a GLAD" << std::endl;
        glfwTerminate();
        return 1;
    }

    Gl::viewport(0, 0, 600, 600);

    Shader vertexShader("assets/shaders/main.vert", Gl::Shader::Type::VERTEX);
    Shader fragmentShader("assets/shaders/main.frag", Gl::Shader::Type::FRAGMENT);

    ShaderProgram shaderProgram(vertexShader.getShader(), fragmentShader.getShader());

    shaderProgram.use();

    Window::Size winSize = window.getFramebufferSize();
    shaderProgram.uniform("uWindowSize", static_cast<GLfloat>(winSize.getX()), static_cast<GLfloat>(winSize.getY()));
    std::vector<GLfloat> vertices =
            {
                    // Перший трикутник (передня сторона)
                    -100,  100, 0.0,   0.0, 0.0, 1.0,   0.0, 1.0,
                    -100, -100, 0.0,   0.0, 0.0, 1.0,   0.0, 0.0,
                    100, -100, 0.0,    0.0, 0.0, 1.0,   1.0, 0.0,

                    -100,  100, 0.0,   0.0, 0.0, 1.0,   0.0, 1.0,
                    100, -100, 0.0,    0.0, 0.0, 1.0,   1.0, 0.0,
                    100, 100, 0.0,     0.0, 0.0, 1.0,   1.0, 1.0,

                    // Другий трикутник (задня сторона)
                    -100,  100, -200.0,   0.0, 0.0, 1.0,   0.0, 1.0,
                    100, -100, -200.0,    0.0, 0.0, 1.0,   1.0, 0.0,
                    -100, -100, -200.0,   0.0, 0.0, 1.0,   0.0, 0.0,

                    -100,  100, -200.0,   0.0, 0.0, 1.0,   0.0, 1.0,
                    100, 100, -200.0,     0.0, 0.0, 1.0,   1.0, 1.0,
                    100, -100, -200.0,    0.0, 0.0, 1.0,   1.0, 0.0,

                    // Третій трикутник (ліва сторона)
                    -100,  100, 0.0,   -1.0, 0.0, 0.0,   0.0, 1.0,
                    -100, -100, -200.0, -1.0, 0.0, 0.0,   1.0, 0.0,
                    -100, -100, 0.0,   -1.0, 0.0, 0.0,   0.0, 0.0,

                    -100,  100, 0.0,   -1.0, 0.0, 0.0,   0.0, 1.0,
                    -100, 100, -200.0,  -1.0, 0.0, 0.0,   1.0, 1.0,
                    -100, -100, -200.0, -1.0, 0.0, 0.0,   1.0, 0.0,

                    // Четвертий трикутник (права сторона)
                    100,  100, 0.0,    1.0, 0.0, 0.0,   0.0, 1.0,
                    100, -100, 0.0,    1.0, 0.0, 0.0,   0.0, 0.0,
                    100, -100, -200.0,  1.0, 0.0, 0.0,   1.0, 0.0,

                    100,  100, 0.0,    1.0, 0.0, 0.0,   0.0, 1.0,
                    100, -100, -200.0,  1.0, 0.0, 0.0,   1.0, 0.0,
                    100, 100, -200.0,   1.0, 0.0, 0.0,   1.0, 1.0,

                    // П'ятий трикутник (верхня сторона)
                    -100, 100, 0.0,    0.0, 1.0, 0.0,   0.0, 1.0,
                    100, 100, -200.0,   0.0, 1.0, 0.0,   1.0, 0.0,
                    -100, 100, -200.0,  0.0, 1.0, 0.0,   0.0, 0.0,

                    -100, 100, 0.0,    0.0, 1.0, 0.0,   0.0, 1.0,
                    100, 100, 0.0,      0.0, 1.0, 0.0,   1.0, 1.0,
                    100, 100, -200.0,   0.0, 1.0, 0.0,   1.0, 0.0,

                    // Шостий трикутник (нижня сторона)
                    -100, -100, 0.0,    0.0, -1.0, 0.0,   0.0, 1.0,
                    -100, -100, -200.0,  0.0, -1.0, 0.0,   0.0, 0.0,
                    100, -100, -200.0,   0.0, -1.0, 0.0,   1.0, 0.0,

                    -100, -100, 0.0,    0.0, -1.0, 0.0,   0.0, 1.0,
                    100, -100, -200.0,   0.0, -1.0, 0.0,   1.0, 0.0,
                    100, -100, 0.0,      0.0, -1.0, 0.0,   1.0, 1.0,
            };
    VAO vao(true, true);
    VBO vbo(vertices);

    vao.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    vao.vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    vao.vertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));

    vao.unbind();
    vbo.unbind();

    Texture texture1(Gl::Texture::Target::Texture2D, Gl::Texture::Wrap::Repeat, Gl::Texture::Wrap::Repeat,
                     Gl::Texture::MinFilter::LinearMipmapLinear, Gl::Texture::MagFilter::Linear);
    texture1.loadImage("container.jpg", true);

    Texture texture2(Gl::Texture::Target::Texture2D, Gl::Texture::Wrap::Repeat, Gl::Texture::Wrap::Repeat,
                   Gl::Texture::MinFilter::LinearMipmapLinear, Gl::Texture::MagFilter::Linear);
    texture2.loadImage("smiley-face.jpg", true);

    float rotateX = 0.f;
    float rotateY = 0.f;
    float rotateZ = 0.f;

    float aspect = (winSize.getY() > 0) ? static_cast<float>(winSize.getX()) / static_cast<float>(winSize.getY()) : 1.0f;
    glm::mat4 projection = glm::perspective(glm::radians(90.f), aspect,0.0001f, 10000.f);
    glm::mat4 view = glm::mat4(1.f);

    shaderProgram.uniform("uProjectionMatrix", 1, GL_FALSE, projection);
    shaderProgram.uniform("uViewMatrix", 1, GL_FALSE, view);
    shaderProgram.uniform("texture1", 0);
    shaderProgram.uniform("texture2", 1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    while(!glfwWindowShouldClose(window.getWinTarget())) { // TODO: Replace it
        window.clearColor(0.2f, 0.3f, 0.3f, 1.f);
        window.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        rotateControl(window, rotateX, rotateY, rotateZ);

        glm::mat4 modelMatrix = glm::mat4(1.0);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -400));

        modelMatrix = glm::rotate(modelMatrix, glm::degrees(rotateX), glm::vec3(1, 0, 0));
        modelMatrix = glm::rotate(modelMatrix, glm::degrees(rotateY), glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix, glm::degrees(rotateZ), glm::vec3(0, 0, 1));

        shaderProgram.uniform("uModelMatrix", 1, GL_FALSE, modelMatrix);

        vao.bind();

        texture1.active(GL_TEXTURE0);
        texture1.bind(Gl::Texture::Target::Texture2D);
        texture2.active(GL_TEXTURE1);
        texture2.bind(Gl::Texture::Target::Texture2D);

        Gl::drawArrays(GL_TRIANGLES, 0, 36);

        window.swapBuffers(window.getWinTarget());
        window.pollEvents();
    }

    return EXIT_SUCCESS;
}
