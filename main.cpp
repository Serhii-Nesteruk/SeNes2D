#include "Objects/Camera/include/Camera.h"
#include "../../Wrappers/include/Window.h"
#include "Objects/Shapes/3D/Cube/include/Cube.h"


#include <iostream>

void rotateControl(Window& window, Cube& cube) {
    static GLfloat rotateX, rotateY, rotateZ;

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

    cube.setRotation(glm::vec3(rotateX, rotateY, rotateZ));
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

    Texture texture1(Gl::Texture::Target::Texture2D, Gl::Texture::Wrap::Repeat, Gl::Texture::Wrap::Repeat,
                     Gl::Texture::MinFilter::LinearMipmapLinear, Gl::Texture::MagFilter::Linear);
    texture1.loadImage("assets/Images/container.jpg", true);

    Texture texture2(Gl::Texture::Target::Texture2D, Gl::Texture::Wrap::Repeat, Gl::Texture::Wrap::Repeat,
                   Gl::Texture::MinFilter::LinearMipmapLinear, Gl::Texture::MagFilter::Linear);
    texture2.loadImage("assets/Images/smiley-face.jpg", true);

    Cube cube(glm::vec3(0.0f, 0.0f, -400.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

    cube.initializeVertices();
    cube.initVAOAndVBO();

    float aspect = (winSize.getY() > 0) ? static_cast<float>(winSize.getX()) / static_cast<float>(winSize.getY()) : 1.0f;
    glm::mat4 projection = glm::perspective(glm::radians(90.f), aspect,0.0001f, 10000.f);
    glm::mat4 view = glm::mat4(1.f);

    shaderProgram.uniform("uProjectionMatrix", 1, GL_FALSE, projection);
    shaderProgram.uniform("uViewMatrix", 1, GL_FALSE, view);
    shaderProgram.uniform("texture1", 0);
    shaderProgram.uniform("texture2", 1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    GLfloat cameraYaw = -90.0f;
    GLfloat cameraPitch = 0.0f;

    Camera camera(cameraPosition, cameraUp, cameraYaw, cameraPitch);

    double lastTime = glfwGetTime();

    GLfloat deltaTime = 0.0f;
    GLint direction = GLFW_KEY_W;
    GLfloat xOffset = 0.0f;
    GLfloat yOffset = 0.0f;

    while(!glfwWindowShouldClose(window.getWinTarget())) { // TODO: Replace it
        window.clearColor(0.2f, 0.3f, 0.3f, 1.f);
        window.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // rotateControl(window, rotateX, rotateY, rotateZ);

      // glm::mat4 modelMatrix = glm::mat4(1.0);
      // modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -400));

      // modelMatrix = glm::rotate(modelMatrix, glm::degrees(rotateX), glm::vec3(1, 0, 0));
      // modelMatrix = glm::rotate(modelMatrix, glm::degrees(rotateY), glm::vec3(0, 1, 0));
      // modelMatrix = glm::rotate(modelMatrix, glm::degrees(rotateZ), glm::vec3(0, 0, 1));

      // shaderProgram.uniform("uModelMatrix", 1, GL_FALSE, modelMatrix);

        double currentTime = glfwGetTime();
        GLfloat deltaTime = static_cast<GLfloat>(currentTime - lastTime);
        lastTime = currentTime;

        if (glfwGetKey(window.getWinTarget(), GLFW_KEY_D) == GLFW_PRESS)
            direction = GLFW_KEY_D;

        if (glfwGetKey(window.getWinTarget(), GLFW_KEY_A) == GLFW_PRESS)
            direction = GLFW_KEY_A;

        if (glfwGetKey(window.getWinTarget(), GLFW_KEY_W) == GLFW_PRESS)
            direction = GLFW_KEY_W;

        if (glfwGetKey(window.getWinTarget(), GLFW_KEY_S) == GLFW_PRESS)
            direction = GLFW_KEY_S;

       camera.processKeyboard(direction, deltaTime);
       camera.processMouseMovement(xOffset, yOffset);

       glm::mat4 viewMatrix = camera.getViewMatrix();
       glm::mat4 projectionMatrix = camera.getProjectionMatrix(winSize.getX(), winSize.getY());

       cube.update(shaderProgram);
       cube.draw(shaderProgram, texture1, texture2);
      // rotateControl(window, cube);

       window.swapBuffers(window.getWinTarget());
       window.pollEvents();
    }

    return EXIT_SUCCESS;
}