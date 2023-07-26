#include "window.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "billboard.hpp"
#include "camera.hpp"

int main()
{
	auto window = skgl::Window::create(800, 600, "skgl imgui test");

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window->m_glfw_window_ptr, true);
	const char* glsl_version = "#version 150";
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Our state
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	skgl::Billboard billboard(skgl::Texture("wall.jpg"));

	skgl::Camera cam;
	skgl::Shader billboard_shader("billboard");

	while (!window->should_close())
	{
		float dt = window->elapsed_time();

		// keyboard processing
		if (!io.WantCaptureKeyboard)
		{
			if (window->is_key_pressed(skgl::Window::keys::escape))
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
				cam.move(dt * cam.get_up());
			if (window->is_key_pressed(skgl::Window::keys::left_shift))
				cam.move(dt * -cam.get_up());

			if (window->is_key_pressed(skgl::Window::keys::q))
				cam.rotate(-dt * 55.f, cam.get_dir());
			if (window->is_key_pressed(skgl::Window::keys::e))
				cam.rotate(dt * 55.f, cam.get_dir());

			if (window->is_key_pressed(skgl::Window::keys::up))
				cam.rotate(dt * 55.f, cam.get_right());
			if (window->is_key_pressed(skgl::Window::keys::down))
				cam.rotate(-dt * 55.f, cam.get_right());
			if (window->is_key_pressed(skgl::Window::keys::left))
				cam.rotate(dt * 55.f, cam.get_up());
			if (window->is_key_pressed(skgl::Window::keys::right))
				cam.rotate(-dt * 55.f, cam.get_up());
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// imgui windows
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");

			ImGui::Text("This is some useful text.");
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
			ImGui::ColorEdit3("clear color", (float*)&clear_color);

			if (ImGui::Button("Button"))
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::Text("Billboard's angle %.6f", billboard.a / 3.1415926535897932385f * 180.f);
			ImGui::End();
		}

		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}

		ImGui::Render();
		window->clear_color = {
			clear_color.x * clear_color.w,
			clear_color.y * clear_color.w,
			clear_color.z * clear_color.w,
			clear_color.w
		};
		window->clear();

		billboard.draw(cam, billboard_shader);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//draw ends

		window->swap_buffers();
		window->poll_events();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();


	return 0;
}