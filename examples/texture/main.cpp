#include "main.hpp"

int main()
{
	auto window = skgl::Window::create(800, 600, "skgl v. alpha 0.0.0.1");

	skgl::Drawable square;
	skgl::Texture texture;

	try
	{
		// change of standart dirs because of the location of an executable after the building
		skgl::Shader::standart_dir = "../../../resources/shaders/";
		skgl::Texture::standart_dir = "../../../resources/textures/";

		texture.init("wall.jpg");

		square.m_shader = skgl::Shader("basic");
		square.m_vao = skgl::VAO(
			(skgl::VBO(vertices)),
			(skgl::EBO(indices))
		);
	}
	catch (const std::exception& e)
	{
		window->destroy();

		std::cout << e.what() << "\n";
		std::cout << "Press any key to continue...\n";
		
		char ch;
		std::cin >> ch;

		return 1;
	}

	square.m_vao.link(0, 3, GL_FLOAT, false,
		sizeof(skgl::Vertex),
		offsetof(skgl::Vertex, skgl::Vertex::m_pos)
	);

	square.m_vao.link(1, 2, GL_FLOAT, false,
		sizeof(skgl::Vertex),
		offsetof(skgl::Vertex, skgl::Vertex::m_tex)
	);

	skgl::Camera cam;
	cam.m_aspect_ratio = 800.f / 600.f;
	cam.m_pos = { 0.f, 0.f, -2.f };


	while (!window->should_close())
	{
		float dt = window->elapsed_time();

		if (window->is_pressed(skgl::Window::keys::q))
			window->set_should_close();

		if (window->is_pressed(skgl::Window::keys::s))
			cam.move(dt * glm::vec3{ 0.f, 0.f, -1.f });

		if (window->is_pressed(skgl::Window::keys::w))
			cam.move(dt * glm::vec3{ 0.f, 0.f, 1.f });

		window->clear();


		texture.bind();
		square.draw(cam);


		window->swap_buffers();
		window->poll_events();
	}


	return 0;
}