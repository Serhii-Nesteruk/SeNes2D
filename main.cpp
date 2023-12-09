#include "Objects/Camera/include/Camera.h"
#include "../../Wrappers/include/Window.h"
#include "Objects/Shapes/3D/Cube/include/Cube.h"


#include <iostream>

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

    Gl::viewport(0, 0, 600, 600); // TODO:

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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    GLfloat cameraYaw = -90.0f;
    GLfloat cameraPitch = 0.0f;

    Camera camera(cameraPosition, cameraUp, cameraYaw, cameraPitch);

    double lastTime = glfwGetTime();

    GLfloat deltaTime = 0.0f;
    GLint direction = 0;
    GLfloat xOffset = 0.0f;
    GLfloat yOffset = 0.0f;

    double mousePosX = 0.f, mousePosY = 0.f;
    double lastMousePosX = 0.f, lastMousePosY = 0.f;
    glfwGetCursorPos(window.getWinTarget(), &mousePosX, &mousePosY);
    lastMousePosX = mousePosX;
    lastMousePosY = mousePosY;

    while(!glfwWindowShouldClose(window.getWinTarget())) { // TODO: Replace it
        window.clearColor(0.2f, 0.3f, 0.3f, 1.f);
        window.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

        //glfwSetCursorPos(window.getWinTarget(), winSize.getX() / 2, winSize.getY() / 2);
        glfwGetCursorPos(window.getWinTarget(), &mousePosX, &mousePosY);
        double mousePosXDelta = lastMousePosX - mousePosX;
        double mousePosYDelta = lastMousePosY - mousePosY;

        lastMousePosX = mousePosX;
        lastMousePosY = mousePosY;

        std::cout << camera.getPosition().x << std::endl;

       camera.processKeyboard(direction, deltaTime);
       camera.processMouseMovement(mousePosXDelta, mousePosYDelta);

       glm::mat4 viewMatrix = camera.getViewMatrix(winSize.getX(), winSize.getY());

       shaderProgram.uniform("uProjectionViewMatrix", 1, GL_FALSE, viewMatrix);
       shaderProgram.uniform("texture1", 0);
       shaderProgram.uniform("texture2", 1);

       cube.update(shaderProgram);
       cube.draw(shaderProgram, texture1, texture2);
      // rotateControl(window, cube);

       window.swapBuffers(window.getWinTarget());
       window.pollEvents();
    }

    return EXIT_SUCCESS;
}
