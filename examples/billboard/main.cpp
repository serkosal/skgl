#include "billboard.hpp"
#include "camera.hpp"
#include "window.hpp"

int main(int argc, char** argv)
{
	auto window = skgl::Window::create(800, 600, "skgl billboard");

	skgl::Billboard billboard;
	billboard.m_texture.init("wall.jpg");

	billboard.m_vao.link(0, 3, GL_FLOAT, false, sizeof(skgl::Vertex), offsetof(skgl::Vertex, skgl::Vertex::m_pos));
	billboard.m_vao.link(1, 3, GL_FLOAT, false, sizeof(skgl::Vertex), offsetof(skgl::Vertex, skgl::Vertex::m_nor));
	billboard.m_vao.link(2, 2, GL_FLOAT, false, sizeof(skgl::Vertex), offsetof(skgl::Vertex, skgl::Vertex::m_tex));

	skgl::Camera cam;
	skgl::Shader billboard_shader("billboard");

	while (!window->should_close())
	{
		float dt = window->elapsed_time();

		if (window->is_pressed(skgl::Window::keys::escape))
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
			cam.move(dt * cam.get_up());
		if (window->is_pressed(skgl::Window::keys::left_shift))
			cam.move(dt * -cam.get_up());

		if (window->is_pressed(skgl::Window::keys::q))
			cam.rotate(-dt * 55.f, cam.get_dir());
		if (window->is_pressed(skgl::Window::keys::e))
			cam.rotate(dt * 55.f, cam.get_dir());

		if (window->is_pressed(skgl::Window::keys::up))
			cam.rotate(dt * 55.f, cam.get_right());
		if (window->is_pressed(skgl::Window::keys::down))
			cam.rotate(-dt * 55.f, cam.get_right());
		if (window->is_pressed(skgl::Window::keys::left))
			cam.rotate(dt * 55.f, cam.get_up());
		if (window->is_pressed(skgl::Window::keys::right))
			cam.rotate(-dt * 55.f, cam.get_up());

		window->clear();


		billboard.draw(cam, billboard_shader);


		window->swap_buffers();
		window->poll_events();
	}




	return 0;
}