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

	window = glfwCreateWindow(size.getX(), size.getY(), title.c_str(), monitor, share);
	if (!window)
		glfwTerminate();

    wasCreated_ = true;
    this->size = size;
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
	glfwMakeContextCurrent(window);
}

GLFWwindow* Window::getWinTarget() const
{
	return window;
}

Window::Window(Size size_, const std::string &title) {
    if (!glfwInit())
        DebugBreak(); // Can't to initialize glfw

    initializeGLFWVersion();
    size = size_;
    create(size, title, nullptr, nullptr);
    makeContextCurrent();
}

bool Window::wasCreated() const {
    return wasCreated_;
}

Window::Size Window::getSize() const {
    return size;
}

Window::Size Window::getFramebufferSize() {
    GLint width = 0, height = 0;
    glfwGetFramebufferSize(window, &width, &height);
    return Window::Size(width, height);
}

void Window::initializeGLFWVersion(int major, int majorValue, int minor, int minorValue) {
    initGLFWVersion(GLFW_CONTEXT_VERSION_MAJOR, 3);
    initGLFWVersion(GLFW_CONTEXT_VERSION_MINOR, 3);
    initGLFWVersion(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

Window::Size::Size(GLint x, GLint y)  : x(x), y(y) {
}

GLint Window::Size::getX() const {
    return x;
}

GLint Window::Size::getY() const {
    return y;
}

void Window::Size::setX(GLint x) {
    this->x = x;
}

void Window::Size::setY(GLint y) {
    this->y = y;
}
