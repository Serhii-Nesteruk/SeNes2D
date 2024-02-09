#include "../include/Window.h"

// clang-format off
#include <Windows.h>
#include <debugapi.h>
// clang-format on

Window::Window()
{
	glfwInit();
}

Window::~Window()
{
	glfwTerminate();
}

void Window::create(Size size, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share)
{
    if (wasCreated())
        DebugBreak(); // You can only create a window once

	_window = glfwCreateWindow(size.getX(), size.getY(), title.c_str(), monitor, share);
	if (!_window)
	{
		DebugBreak(); // Window was not created
	}

    _wasCreated = true;
    this->_size = size;
}

void Window::swapBuffers(GLFWwindow* window)
{
	glfwSwapBuffers(window);
}

void Window::pollEvents()
{
	glfwPollEvents();
}

void Window::clear(GLbitfield mask)
{
	glClear(mask);
}

void Window::clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	glClearColor(red, green, blue, alpha);
}

void Window::initGLFWVersion(int hint, int value)
{
	glfwWindowHint(hint, value);
}

void Window::makeContextCurrent()
{
	glfwMakeContextCurrent(_window);
}

GLFWwindow* Window::getWinTarget() const
{
	return _window;
}

Window::Window(Size size, const std::string &title) {
    if (!glfwInit())
        DebugBreak(); // Can't to initialize glfw

    initializeGLFWVersion();
    _size = size;
    create(_size, title, nullptr, nullptr);
    makeContextCurrent();
}

bool Window::wasCreated() const {
    return _wasCreated;
}

Window::Size Window::getSize() const {
    return _size;
}

Window::Size Window::getFramebufferSize() {
    GLint width = 0, height = 0;
    glfwGetFramebufferSize(_window, &width, &height);
    return Window::Size(width, height);
}

void Window::initializeGLFWVersion(int major, int majorValue, int minor, int minorValue) {
    initGLFWVersion(GLFW_CONTEXT_VERSION_MAJOR, 3);
    initGLFWVersion(GLFW_CONTEXT_VERSION_MINOR, 3);
    initGLFWVersion(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}
bool Window::shouldClose()
{
	return glfwWindowShouldClose(_window);
}

Window::Size::Size(GLint x, GLint y)  : _x(x), _y(y) {
}

GLint Window::Size::getX() const {
    return _x;
}

GLint Window::Size::getY() const {
    return _y;
}

void Window::Size::setX(GLint x) {
    this->_x = x;
}

void Window::Size::setY(GLint y) {
    this->_y = y;
}
