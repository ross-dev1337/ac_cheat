#include "dll_main.h"

void _interface::init_menu() {
	if (GetAsyncKeyState('O') & 0x1)
		toggle_menu();
	draw_menu();
}

void _interface::draw_menu() {
	if (globals::vars::menu_settings::menu_open) {

		POINT mousePos = { 0.f, 0.f };

		GetCursorPos(&mousePos);
		ScreenToClient(globals::vars::window, &mousePos);

		ImGui::GetIO().MousePos = ImVec2(mousePos.x, mousePos.y);
		ImGui::GetIO().MouseDown[0] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) ? true : false;

		ImGuiStyle& style = ImGui::GetStyle();
		ImGuiIO& io = ImGui::GetIO();
		style.WindowPadding = ImVec2(5, 5);
		style.WindowRounding = 5.f;
		style.FramePadding = ImVec2(2, 2);
		style.FrameRounding = 5.f;
		style.ItemSpacing = ImVec2(12, 8);
		style.ItemInnerSpacing = ImVec2(4, 3);
		style.IndentSpacing = 25.f;
		style.ItemSpacing = ImVec2(5, 5);
		style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
		style.GrabRounding = 5.f;

		io.WantCaptureKeyboard = true;
		io.WantCaptureMouse = true;

		style.WindowMinSize.x = 400;
		style.WindowMinSize.y = 400;

		if (ImGui::Begin("ac_cheat")) {
			ImGui::Text("Aimbot setting");
			ImGui::Checkbox("Aimbot", &globals::vars::menu_settings::aimbot::enable_aimbot);
			ImGui::Checkbox("Visible Check", &globals::vars::menu_settings::aimbot::vis_check);
		
			ImGui::Separator();

			ImGui::Text("Visual Settings");
			ImGui::Checkbox("Draw Snap Lines", &globals::vars::menu_settings::visuals::snap_lines);
			ImGui::Checkbox("Draw Names+Distance", &globals::vars::menu_settings::visuals::names_distance);
			ImGui::Checkbox("Draw Box", &globals::vars::menu_settings::visuals::box);
		}
	}
}

void _interface::toggle_menu() {
	!globals::vars::menu_settings::menu_open ? globals::vars::menu_settings::menu_open = true : globals::vars::menu_settings::menu_open = false;
	functions::SDL2::SDL_SetRelativeMouseMove(!globals::vars::menu_settings::menu_open);
}



