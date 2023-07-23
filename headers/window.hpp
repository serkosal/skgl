#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string_view>
#include <memory>

#include <glm/glm.hpp>

namespace skgl {

using Coord = glm::vec<2, double>;

class Window
{
	
// Data

	double m_old_time;
	Coord m_old_mouse_pos;

	static std::unique_ptr<Window> sm_instance;

	struct Color
	{
		float r, g, b, a;
	};
public:
	GLFWwindow* m_ptr = nullptr;
	mutable Color clear_color = { 0.f, 0.f, 0.f, 1.f };

// Enums

	enum class keys
	{
		space = GLFW_KEY_SPACE,
		apostrophe = GLFW_KEY_APOSTROPHE,
		comma = GLFW_KEY_COMMA,
		minus = GLFW_KEY_MINUS,
		period = GLFW_KEY_PERIOD,
		slash = GLFW_KEY_SLASH,

		_0 = GLFW_KEY_0,
		_1, _2, _3, _4, _5, _6, _7, _8,
		_9,

		semicolon = GLFW_KEY_SEMICOLON,
		equal = GLFW_KEY_EQUAL,

		a = GLFW_KEY_A,
		b, c, d, e, f, g, h, i, j, k, l, m,
		n, o, p, q, r, s, t, u, v, w, x, y,
		z,

		escape = GLFW_KEY_ESCAPE,
		enter,
		tab,
		backspace,
		insert,
		del,
		right,
		left,
		down,
		up,
		page_up,
		page_down,
		home,
		end,

		caps_lock = GLFW_KEY_CAPS_LOCK,
		scroll_lock,
		num_lock,
		print_screen,
		pause,

		f1 = GLFW_KEY_F1,
		f2, f3, f4, f5, f6, f7, f8, f9, f10, f11,
		f12,

		num_0 = GLFW_KEY_KP_0,
		num_1, num_2, num_3, num_4,
		num_5, num_6, num_7, num_8,
		num_9,

		num_decimal,
		num_divide,
		num_multiply,
		num_subtract,
		num_add,
		num_enter,
		num_equal,

		left_shift = GLFW_KEY_LEFT_SHIFT,
		left_ctrl,
		left_alt,
		left_super,

		right_shift,
		right_ctrl,
		right_alt,
		right_super,
	};
	enum class mouse
	{
		left = GLFW_MOUSE_BUTTON_LEFT,
		right = GLFW_MOUSE_BUTTON_RIGHT,
		midle = GLFW_MOUSE_BUTTON_MIDDLE,

		_4 = GLFW_MOUSE_BUTTON_4,
		_5 = GLFW_MOUSE_BUTTON_5
	};
	enum class cursor_modes
	{
		normal = GLFW_CURSOR_NORMAL,
		hidden = GLFW_CURSOR_HIDDEN,
		disabled = GLFW_CURSOR_DISABLED,
		captured = GLFW_CURSOR_CAPTURED
	};


// Methods

public:
	static Window* create(int width = 800, int height = 600, std::string_view title = "OpenGL", bool is_fullscreen = false);
	static Window* instance();
	static void destroy();


	bool should_close() const;
	void clear() const;

	void set_should_close(bool close = true);

	void set_title(std::string_view title);
	void set_icon(int count, GLFWimage* images);

	void set_cursor_mode(Window::cursor_modes mode);

	void swap_buffers() const;
	void poll_events()  const;
	void wait_events()  const;

	double get_time() const;
	double elapsed_time();

	Coord get_size() const;
	double aspect_ratio() const;

	bool is_pressed(Window::keys key) const;
	bool is_pressed(Window::mouse button = Window::mouse::left) const;

	Coord get_mouse_pos() const;
	Coord get_mouse_offset();


	~Window();

	Window(const Window& other) = delete;
	Window& operator=(const Window& other) = delete;
	Window(Window&& other) = delete;
	Window& operator=(Window&& other) = delete;

protected:
	Window(
		int width = 800, 
		int height = 600, 
		std::string_view title = "OpenGL", 
		bool is_fullscreen = false
	);
};

} // namespace skgl

#endif // !WINDOW_HPP
