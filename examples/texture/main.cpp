#include <iostream>

#include "window.hpp"

#include "shader.hpp"
#include "texture.hpp"

#include "shapes.hpp"

#include "camera.hpp"

int main()
{
	auto window = skgl::Window::create(800, 600, "skgl texture");
	window->set_cursor_mode(skgl::Window::cursor_modes::disabled);

	skgl::Texture texture;
	skgl::Shader basic_shader;
	auto quad = skgl::Shapes::Quad();

	try
	{
		texture.init("wall.jpg");
		basic_shader.init("texture");
	}
	catch (const std::exception& e)
	{
		window->destroy();

		std::cout << e.what() << "\n\n";
		std::cout << "Press any key to continue...\n";
		
		char ch;
		std::cin >> ch;

		return 1;
	}

	skgl::Camera cam;
	cam.m_pos = { 0.f, 0.f, -2.f };

	basic_shader.bind();
	texture.bind();
	basic_shader.setMat4("model", glm::mat4(1.f));


	while (!window->should_close())
	{
		float dt = window->elapsed_time();

		// get and process cursor movements
		{
			auto offset = window->get_mouse_offset();
			cam.rotate(dt * 30 * offset.x, {0, 1, 0});
			cam.rotate(dt * 30 * offset.y, cam.get_right());
		}
			

		if (window->is_key_pressed(skgl::Window::keys::q))
			window->set_should_close();

		if (window->is_key_pressed(skgl::Window::keys::s))
			cam.move(dt * -cam.get_dir());

		if (window->is_key_pressed(skgl::Window::keys::w))
			cam.move(dt * cam.get_dir());

		if (window->is_key_pressed(skgl::Window::keys::a))
			cam.move(dt * -cam.get_right());

		if (window->is_key_pressed(skgl::Window::keys::d))
			cam.move(dt * cam.get_right());

		if (window->is_key_pressed(skgl::Window::keys::space))
			cam.move(dt * glm::vec3{0, 1, 0});
		if (window->is_key_pressed(skgl::Window::keys::left_shift))
			cam.move(dt * glm::vec3{0, -1, 0});

		window->clear();

		cam.m_aspect_ratio = window->aspect_ratio();
		basic_shader.setMat4("proj", cam.get_proj());

		basic_shader.setMat4("view", cam.look_at());


		quad.draw();


		window->swap_buffers();
		window->poll_events();
	}


	return 0;
}