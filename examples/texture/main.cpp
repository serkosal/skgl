#include "main.hpp"

int main()
{
	auto window = skgl::Window::create(800, 600, "skgl v. alpha 0.0.0.1");

	skgl::Drawable square(
		(skgl::Shader("basic")),
		(skgl::VAO(
			(skgl::VBO(vertices)),
			(skgl::EBO(indices)))
		)
	);

	square.m_vao.link(0, 3, GL_FLOAT, false, 
		sizeof(skgl::Vertex), 
		offsetof(skgl::Vertex, skgl::Vertex::m_pos)
	);

	square.m_vao.link(1, 2, GL_FLOAT, false, 
		sizeof(skgl::Vertex), 
		offsetof(skgl::Vertex, skgl::Vertex::m_tex)
	);

	skgl::Texture texture("wall.jpg");


	while (!window->should_close())
	{
		window->clear();

		
		texture.bind();
		square.draw();
		

		window->swap_buffers();
		window->wait_events();
	}


    return 0;
}