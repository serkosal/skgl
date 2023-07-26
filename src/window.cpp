#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

	m_glfw_window_ptr = glfwCreateWindow(width, height, title.data(),
		is_fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);

	if (m_glfw_window_ptr == nullptr)
	{
		skgl::log("GLFW Couldn't create window!");
		throw std::runtime_error("Failed to create GLFW window!\n");
	}
	else
		skgl::log("GLFW successfully created window.");
		

	glfwMakeContextCurrent((GLFWwindow*)m_glfw_window_ptr);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		skgl::log("Failed to initialize GLAD!");
		throw std::runtime_error("Failed to initialize GLAD");
	}
	else
		skgl::log("Successfully initialized GLAD.");

	glViewport(0, 0, width, height);

	glfwSetFramebufferSizeCallback((GLFWwindow*)m_glfw_window_ptr,
		[](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}
	);

	m_old_time = glfwGetTime();
	glfwGetCursorPos((GLFWwindow*)m_glfw_window_ptr, &m_old_mouse_pos.x, &m_old_mouse_pos.y);

	glEnable(GL_DEPTH_TEST);
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
	return static_cast<bool>(glfwWindowShouldClose((GLFWwindow*)m_glfw_window_ptr));
}

void Window::clear() const
{
	glClearColor(clear_color.r, clear_color.b, clear_color.b, clear_color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::set_should_close(bool close)
{
	glfwSetWindowShouldClose((GLFWwindow*)m_glfw_window_ptr, close);
}

void Window::set_title(std::string_view title)
{
	glfwSetWindowTitle((GLFWwindow*)m_glfw_window_ptr, title.data());
}

void Window::set_icon(int count, void* images)
{
	glfwSetWindowIcon((GLFWwindow*)m_glfw_window_ptr, count, (GLFWimage*)images);
}

void Window::set_cursor_mode(Window::Cursor_mode mode)
{
	glfwSetInputMode((GLFWwindow*)m_glfw_window_ptr, GLFW_CURSOR, int(mode));
}

void Window::swap_buffers() const { glfwSwapBuffers((GLFWwindow*)m_glfw_window_ptr); }
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
	glfwGetWindowSize((GLFWwindow*)m_glfw_window_ptr, &x, &y);
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
	glfwGetCursorPos((GLFWwindow*)m_glfw_window_ptr, &m_pos.x, &m_pos.y);

	return m_pos;
}

Coord Window::get_mouse_offset()
{
	Coord new_pos = get_mouse_pos();

	Coord offset = m_old_mouse_pos - new_pos;

	m_old_mouse_pos = new_pos;

	return offset;
}

bool Window::is_key_pressed(Window::Key key) const
{
	return glfwGetKey((GLFWwindow*)m_glfw_window_ptr, key);
}

bool Window::is_mouse_clicked(Window::Mouse_button button) const
{
	return glfwGetMouseButton((GLFWwindow*)m_glfw_window_ptr, button);
}

Window::~Window()
{
	skgl::log("Window's destructor invoked.");
	glfwTerminate();
	skgl::log("GLFW terminated.");
}

Window::Key
Window::keys::space					= GLFW_KEY_SPACE,
Window::keys::apostrophe			= GLFW_KEY_APOSTROPHE,
Window::keys::comma					= GLFW_KEY_COMMA,
Window::keys::minus					= GLFW_KEY_MINUS,
Window::keys::period				= GLFW_KEY_PERIOD,
Window::keys::slash					= GLFW_KEY_SLASH,

Window::keys::_0					= GLFW_KEY_0,
Window::keys::_1					= GLFW_KEY_1,
Window::keys::_2					= GLFW_KEY_2,
Window::keys::_3					= GLFW_KEY_3,
Window::keys::_4					= GLFW_KEY_4,
Window::keys::_5					= GLFW_KEY_5,
Window::keys::_6					= GLFW_KEY_6,
Window::keys::_7					= GLFW_KEY_7,
Window::keys::_8					= GLFW_KEY_8,
Window::keys::_9					= GLFW_KEY_9,

Window::keys::semicolon				= GLFW_KEY_SEMICOLON,
Window::keys::equal					= GLFW_KEY_EQUAL,

Window::keys::a						= GLFW_KEY_A,
Window::keys::b						= GLFW_KEY_B,
Window::keys::c						= GLFW_KEY_C,
Window::keys::d						= GLFW_KEY_D,
Window::keys::e						= GLFW_KEY_E,
Window::keys::f						= GLFW_KEY_F,
Window::keys::g						= GLFW_KEY_G,
Window::keys::h						= GLFW_KEY_H,
Window::keys::i						= GLFW_KEY_I,
Window::keys::j						= GLFW_KEY_J,
Window::keys::k						= GLFW_KEY_K,
Window::keys::l						= GLFW_KEY_L,
Window::keys::m						= GLFW_KEY_M,
Window::keys::n						= GLFW_KEY_N,
Window::keys::o						= GLFW_KEY_O,
Window::keys::p						= GLFW_KEY_P,
Window::keys::q						= GLFW_KEY_Q,
Window::keys::r						= GLFW_KEY_R,
Window::keys::s						= GLFW_KEY_S,
Window::keys::t						= GLFW_KEY_T,
Window::keys::u						= GLFW_KEY_U,
Window::keys::v						= GLFW_KEY_V,
Window::keys::w						= GLFW_KEY_W,
Window::keys::x						= GLFW_KEY_X,
Window::keys::y						= GLFW_KEY_Y,
Window::keys::z						= GLFW_KEY_Z,

Window::keys::escape				= GLFW_KEY_ESCAPE,
Window::keys::enter					= GLFW_KEY_ENTER,
Window::keys::tab					= GLFW_KEY_TAB,
Window::keys::backspace				= GLFW_KEY_BACKSPACE,
Window::keys::insert				= GLFW_KEY_INSERT,
Window::keys::del					= GLFW_KEY_DELETE,
Window::keys::right					= GLFW_KEY_RIGHT,
Window::keys::left					= GLFW_KEY_LEFT,
Window::keys::down					= GLFW_KEY_DOWN,
Window::keys::up					= GLFW_KEY_UP,
Window::keys::page_up				= GLFW_KEY_PAGE_UP,
Window::keys::page_down				= GLFW_KEY_PAGE_DOWN,
Window::keys::home					= GLFW_KEY_HOME,
Window::keys::end					= GLFW_KEY_END,

Window::keys::caps_lock				= GLFW_KEY_CAPS_LOCK,
Window::keys::scroll_lock			= GLFW_KEY_SCROLL_LOCK,
Window::keys::num_lock				= GLFW_KEY_NUM_LOCK,
Window::keys::print_screen			= GLFW_KEY_PRINT_SCREEN,
Window::keys::pause					= GLFW_KEY_PAUSE,

Window::keys::f1					= GLFW_KEY_F1,
Window::keys::f2					= GLFW_KEY_F2,
Window::keys::f3					= GLFW_KEY_F3,
Window::keys::f4					= GLFW_KEY_F4,
Window::keys::f5					= GLFW_KEY_F5,
Window::keys::f6					= GLFW_KEY_F6,
Window::keys::f7					= GLFW_KEY_F7,
Window::keys::f8					= GLFW_KEY_F8,
Window::keys::f9					= GLFW_KEY_F9,
Window::keys::f10					= GLFW_KEY_F10,
Window::keys::f11					= GLFW_KEY_F11,
Window::keys::f12					= GLFW_KEY_F12,

Window::keys::num_0					= GLFW_KEY_KP_0,
Window::keys::num_1					= GLFW_KEY_KP_1,
Window::keys::num_2					= GLFW_KEY_KP_2,
Window::keys::num_3					= GLFW_KEY_KP_3,
Window::keys::num_4					= GLFW_KEY_KP_4,
Window::keys::num_5					= GLFW_KEY_KP_5,
Window::keys::num_6					= GLFW_KEY_KP_6,
Window::keys::num_7					= GLFW_KEY_KP_7,
Window::keys::num_8					= GLFW_KEY_KP_8,
Window::keys::num_9					= GLFW_KEY_KP_9,

Window::keys::num_decimal			= GLFW_KEY_KP_DECIMAL,
Window::keys::num_divide			= GLFW_KEY_KP_DIVIDE,
Window::keys::num_multiply			= GLFW_KEY_KP_MULTIPLY,
Window::keys::num_subtract			= GLFW_KEY_KP_SUBTRACT,
Window::keys::num_add				= GLFW_KEY_KP_ADD,
Window::keys::num_enter				= GLFW_KEY_KP_ENTER,
Window::keys::num_equal				= GLFW_KEY_KP_EQUAL,

Window::keys::left_shift			= GLFW_KEY_LEFT_SHIFT,
Window::keys::left_ctrl				= GLFW_KEY_LEFT_CONTROL,
Window::keys::left_alt				= GLFW_KEY_LEFT_ALT,
Window::keys::left_super			= GLFW_KEY_LEFT_SUPER,

Window::keys::right_shift			= GLFW_KEY_RIGHT_SHIFT,
Window::keys::right_ctrl			= GLFW_KEY_RIGHT_CONTROL,
Window::keys::right_alt				= GLFW_KEY_RIGHT_ALT,
Window::keys::right_super			= GLFW_KEY_RIGHT_SUPER;


Window::Mouse_button
Window::mouse_buttons::left			= GLFW_MOUSE_BUTTON_LEFT,
Window::mouse_buttons::right		= GLFW_MOUSE_BUTTON_RIGHT,
Window::mouse_buttons::midle		= GLFW_MOUSE_BUTTON_MIDDLE,

Window::mouse_buttons::_4			= GLFW_MOUSE_BUTTON_4,
Window::mouse_buttons::_5			= GLFW_MOUSE_BUTTON_5;


Window::Cursor_mode
Window::cursor_modes::normal		= GLFW_CURSOR_NORMAL,
Window::cursor_modes::hidden		= GLFW_CURSOR_HIDDEN,
Window::cursor_modes::disabled		= GLFW_CURSOR_DISABLED,
Window::cursor_modes::captured		= GLFW_CURSOR_CAPTURED;