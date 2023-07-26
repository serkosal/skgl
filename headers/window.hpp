#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP

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
	void* m_glfw_window_ptr = nullptr;
	mutable Color clear_color = { 0.f, 0.f, 0.f, 1.f };

// Enums
	using Key = int;
	struct keys
	{
		static Key
			space,
			apostrophe,
			comma,
			minus,
			period,
			slash,

			_0,
			_1, _2, _3, _4, _5, _6, _7, _8,
			_9,

			semicolon,
			equal,

			a,
			b, c, d, e, f, g, h, i, j, k, l, m,
			n, o, p, q, r, s, t, u, v, w, x, y,
			z,

			escape,
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

			caps_lock,
			scroll_lock,
			num_lock,
			print_screen,
			pause,

			f1,
			f2, f3, f4, f5, f6, f7, f8, f9, f10, f11,
			f12,

			num_0,
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

			left_shift,
			left_ctrl,
			left_alt,
			left_super,

			right_shift,
			right_ctrl,
			right_alt,
			right_super;
	};

	using Mouse_button = int;
	struct mouse_buttons
	{
		static Mouse_button
			left,
			right,
			midle,

			_4,
			_5;
	};

	using Cursor_mode = int;
	struct cursor_modes
	{
		static Cursor_mode
			normal,
			hidden,
			disabled,
			captured;
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
	void set_icon(int count, void* glfw_images);

	void set_cursor_mode(Window::Cursor_mode mode);

	void swap_buffers() const;
	void poll_events()  const;
	void wait_events()  const;

	double get_time() const;
	double elapsed_time();

	Coord get_size() const;
	double aspect_ratio() const;

	bool is_key_pressed(Window::Key key) const;
	bool is_mouse_clicked(Window::Mouse_button button = Window::mouse_buttons::left) const;

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
