#include "window.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "camera.hpp"
#include "shader.hpp"
#include "model.hpp"
#include "light.hpp"

#include <iostream>

int main(int argc, char** argv)
{
	skgl::Shader basic_shader;

	skgl::Model model;

	try
	{
		skgl::Window::create(800, 600, "skgl model");
		basic_shader.init("model");
		model.init("model/scene.gltf", true);
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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window->m_ptr, true);
	const char* glsl_version = "#version 150";
	ImGui_ImplOpenGL3_Init(glsl_version);


	skgl::Camera cam;
	skgl::Light light({ 0.f, 2.f, 0.f }, { 1.f, 1.f, 1.f });

	while (!window->should_close())
	{
		float dt = window->elapsed_time();

		// get and process cursor movements
		/*
		if (!io.WantCaptureMouse)
		{
			auto offset = window->get_mouse_offset();
			cam.rotate(dt * 30 * offset.x, { 0, 1, 0 });
			cam.rotate(dt * 30 * offset.y, cam.get_right());
		}
		*/

		// process keyboard
		if (!io.WantCaptureKeyboard)
		{
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
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// imgui window
		{

			ImGui::Begin("Model example!");

			ImGui::Text("This is some useful text.");

			ImGui::ColorEdit4("clear color", (float*)&window->clear_color.r);

			ImGui::InputFloat("Light x:", &light.m_pos.x, 0.1f, 0.2f);
			ImGui::InputFloat("y:", &light.m_pos.y, 0.1f, 0.2f);
			ImGui::InputFloat("z:", &light.m_pos.z, 0.1f, 0.2f);

			ImGui::ColorEdit3("light color", (float*)&light.m_color.x);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
		}

		ImGui::Render();
		window->clear();

		cam.m_aspect_ratio = window->aspect_ratio();

		light.apply(basic_shader);
		model.draw(cam, basic_shader);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window->swap_buffers();
		window->poll_events();
	}


	return 0;
}