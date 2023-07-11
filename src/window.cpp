#include <stdexcept>

#include "window.hpp"

using namespace skgl;

std::unique_ptr<Window> Window::_instance;

Window::Window(int width, int height, std::string_view title, bool is_fullscreen)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	ptr = glfwCreateWindow(width, height, title.data(), NULL, NULL);

	if (ptr == nullptr)
		throw std::runtime_error("Failed to create GLFW window!\n");

	glfwMakeContextCurrent(ptr);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("Failed to initialize GLAD");

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(ptr,
		[](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}
	);
}

Window* Window::create(int width, int height, std::string_view title, bool is_fullscreen)
{
	if (!_instance)
	{
		Window* window_temp = new Window(width, height, title, is_fullscreen);
		_instance = std::unique_ptr<Window>(window_temp);
	}
		

	return _instance.get();
}

Window* Window::instance()
{
	return _instance.get();
}

void Window::destroy()
{
	Window::instance()->~Window();
}