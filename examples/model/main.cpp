#include "window.hpp"
#include "camera.hpp"
#include "shader.hpp"
#include "model.hpp"

#include <filesystem>
#include <iostream>

int main(int argc, char** argv)
{
	skgl::Shader basic_shader;

	skgl::Model model;

	try
	{
		skgl::Window::create(1980, 1080, "skgl texture", true);
		basic_shader.init("model");
		model.init("model/scene.gltf");
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception was thrown!\n:" << e.what() << "\n\n";
		skgl::Window::destroy();
		char ch;
		std::cin >> ch;
		return -1;
	}
	
	auto window = skgl::Window::instance();
	window->set_cursor_mode(skgl::Window::cursor_modes::disabled);

	skgl::Camera cam;

	while (!window->should_close())
	{
		float dt = window->elapsed_time();

		// get and process cursor movements 
		{
			auto offset = window->get_mouse_offset();
			cam.rotate(dt * 30 * offset.x, { 0, 1, 0 });
			cam.rotate(dt * 30 * offset.y, cam.get_right());
		}


		if (window->is_pressed(skgl::Window::keys::q))
			window->set_should_close();

		if (window->is_pressed(skgl::Window::keys::s))
			cam.move(dt * -cam.get_dir());

		if (window->is_pressed(skgl::Window::keys::w))
			cam.move(dt * cam.get_dir());

		if (window->is_pressed(skgl::Window::keys::a))
			cam.move(dt * -cam.get_right());

		if (window->is_pressed(skgl::Window::keys::d))
			cam.move(dt * cam.get_right());

		if (window->is_pressed(skgl::Window::keys::space))
			cam.move(dt * glm::vec3{0, 1, 0});
		if (window->is_pressed(skgl::Window::keys::left_shift))
			cam.move(dt * glm::vec3{0, -1, 0});

		window->clear();


		model.draw(cam, basic_shader);


		window->swap_buffers();
		window->poll_events();
	}


	return 0;
}