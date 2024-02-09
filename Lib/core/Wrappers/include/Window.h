#pragma once

#include "Gl.h"

#include <string>

class Window {
public:
    struct Size {
        Size() = default;
        Size(GLint x, GLint y);

        [[nodiscard]] GLint getX() const;
        [[nodiscard]] GLint getY() const;
        void setX(GLint x);
        void setY(GLint y);
    private:
        GLint _x = 0, _y = 0;
    };

	Window();
    Window(Size size, const std::string& title);
	~Window();

	void create(Size size, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share);
	void swapBuffers(GLFWwindow* window);
	void pollEvents();
	void clear(GLbitfield mask);
	void clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	void initGLFWVersion(int hint, int value);
	void makeContextCurrent();
    Size getFramebufferSize();
	[[nodiscard]] bool shouldClose();

    [[nodiscard]] Size getSize() const;

    [[nodiscard]] bool wasCreated() const;

	[[nodiscard]] GLFWwindow* getWinTarget() const;
    void initializeGLFWVersion(int major = GLFW_CONTEXT_VERSION_MAJOR, int majorValue = 3,
                               int minor = GLFW_CONTEXT_VERSION_MINOR, int minorValue = 3);
private:
    bool _wasCreated = false;
    Size _size;
	GLFWwindow* _window = nullptr;
};