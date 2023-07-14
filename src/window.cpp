#include <stdexcept>

#include "log.hpp"
#include "window.hpp"

using namespace skgl;

std::unique_ptr<Window> Window::sm_instance;

Window::Window(int width, int height, std::string_view title, bool is_fullscreen)
{
	skgl::log("Window constructor invoked");

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	skgl::log("GLFW Inited");

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	m_ptr = glfwCreateWindow(width, height, title.data(), 
		is_fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);

	if (m_ptr == nullptr)
	{
		skgl::log("GLFW Couldn't create window!");
		throw std::runtime_error("Failed to create GLFW window!\n");
	}
	else
		skgl::log("GLFW successfully created window.");
		

	glfwMakeContextCurrent(m_ptr);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		skgl::log("Failed to initialize GLAD!");
		throw std::runtime_error("Failed to initialize GLAD");
	}
	else
		skgl::log("Successfully initialized GLAD.");
		

	glViewport(0, 0, width, height);

	glfwSetFramebufferSizeCallback(m_ptr,
		[](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}
	);

	m_old_time = glfwGetTime();
	glfwGetCursorPos(m_ptr, &m_old_mouse_pos.x, &m_old_mouse_pos.y);
}

Window* Window::create(int width, int height, std::string_view title, bool is_fullscreen)
{
	skgl::log("skgl::Window::create() function called.");

	if (!sm_instance)
	{
		Window* window_temp = new Window(width, height, title, is_fullscreen);
		sm_instance = std::unique_ptr<Window>(window_temp);
	}
		

	return sm_instance.get();
}

Window* Window::instance()
{
	return sm_instance.get();
}

void Window::destroy()
{
	skgl::log("skgl::Window::destroy() function called.");
	Window::instance()->~Window();
}

bool Window::should_close() const
{
	return static_cast<bool>(glfwWindowShouldClose(m_ptr));
}

void Window::clear() const
{
	glClearColor(clear_color.r, clear_color.b, clear_color.b, clear_color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::set_should_close(bool close)
{
	glfwSetWindowShouldClose(m_ptr, close);
}

void Window::set_title(std::string_view title)
{
	glfwSetWindowTitle(m_ptr, title.data());
}

void Window::set_icon(int count, GLFWimage* images)
{
	glfwSetWindowIcon(m_ptr, count, images);
}

void Window::set_cursor_mode(Window::cursor_modes mode)
{
	glfwSetInputMode(m_ptr, GLFW_CURSOR, int(mode));
}

void Window::swap_buffers() const { glfwSwapBuffers(m_ptr); }
void Window::poll_events() const { glfwPollEvents(); }
void Window::wait_events() const { glfwWaitEvents(); }

double Window::get_time() const
{
	return glfwGetTime();
}

double Window::elapsed_time()
{
	double dt = glfwGetTime() - m_old_time;

	m_old_time += dt;

	return dt;
}

Coord Window::get_size() const
{
	int x, y;
	glfwGetWindowSize(m_ptr, &x, &y);
	return {x, y};
}

double Window::aspect_ratio() const
{
	auto size = get_size();
	return size.x / size.y;
}

Coord Window::get_mouse_pos() const
{
	Coord m_pos;
	glfwGetCursorPos(m_ptr, &m_pos.x, &m_pos.y);

	return m_pos;
}

Coord Window::get_mouse_offset()
{
	Coord new_pos = get_mouse_pos();

	Coord offset = m_old_mouse_pos - new_pos;

	m_old_mouse_pos = new_pos;

	return offset;
}

bool Window::is_pressed(Window::keys key) const
{
	return glfwGetKey(m_ptr, int(key));
}

bool Window::is_pressed(Window::mouse button) const
{
	return glfwGetMouseButton(m_ptr, int(button));
}

 Window::~Window()
{
	skgl::log("Window's destructor invoked.");
	glfwTerminate();
	skgl::log("GLFW terminated.");
}