#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string_view>
#include <memory>

#include <glm/glm.hpp>

namespace skgl {

class Window
{
	
// Data

	GLFWwindow* ptr = nullptr;
	static std::unique_ptr<Window> _instance;

	struct Color
	{
		float r, g, b, a;
	};
public:
	mutable Color clear_color = { 0.f, 0.f, 0.f, 1.f };


// Methods

public:
	static Window* create(int width = 800, int height = 600, std::string_view title = "OpenGL", bool is_fullscreen = false);
	static Window* instance();
	static void destroy();


	bool should_close() const { return static_cast<bool>(glfwWindowShouldClose(ptr)); }
	void clear() const
	{
		glClearColor(clear_color.r, clear_color.b, clear_color.b, clear_color.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void swap_buffers() const { glfwSwapBuffers(ptr); }
	void poll_events() const { glfwPollEvents(); }
	void wait_events() const { glfwWaitEvents(); }

	~Window() 
	{
		if (ptr)
			glfwTerminate();
	}

	Window(const Window& other) = delete;
	Window& operator=(const Window& other) = delete;
	Window(Window&& other) = delete;
	Window& operator=(Window&& other) = delete;

protected:
	Window(int width = 800, int height = 600, std::string_view title = "OpenGL", bool is_fullscreen = false);
};

} // namespace skgl

#endif // !WINDOW_HPP
