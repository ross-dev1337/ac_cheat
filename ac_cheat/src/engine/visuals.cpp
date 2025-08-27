#include "dll_main.h"


void visuals::drawing::draw_text(const char* text, float x, float y, ImVec4 color, bool is_outlined, ImVec4 outlined_color) {
	if (is_outlined)
	{
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x - 1.5f, y - 1.5f), ImGui::GetColorU32(outlined_color), text);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y - 1.5f), ImGui::GetColorU32(outlined_color), text);

		ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1.5f, y - 1.5f), ImGui::GetColorU32(outlined_color), text);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1.5f, y), ImGui::GetColorU32(outlined_color), text);

		ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1.5f, y + 1.5f), ImGui::GetColorU32(outlined_color), text);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y + 1.5f), ImGui::GetColorU32(outlined_color), text);

		ImGui::GetOverlayDrawList()->AddText(ImVec2(x - 1.5f, y + 1.5f), ImGui::GetColorU32(outlined_color), text);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x - 1.5f, y), ImGui::GetColorU32(outlined_color), text);
	}

	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::GetColorU32(color), text);
}

void visuals::drawing::draw_rect(float x, float y, float width, float height, ImVec4 color) {
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + width, y + height), ImGui::GetColorU32(ImVec4(color.x, color.y, color.z, color.w)));
}

void visuals::drawing::draw_string(const char* string, float x, float y, ImVec4 color) {
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::GetColorU32(ImVec4(color.x, color.y, color.z, color.w)), string, NULL);
}

void visuals::drawing::draw_text_shader(const char* string, float x, float y, ImVec4 color, ImVec4 color2, globals::vars::align op) {
	ImVec2 textSize = ImGui::CalcTextSize(string, NULL);
	ImVec2 textWidth(textSize.x, textSize.y);

	if (op & globals::vars::ALIGN_X_LEFT)
		x = x;
	if (op & globals::vars::ALIGN_X_CENTER)
		x = x - (textWidth.x / 2);
	if (op & globals::vars::ALIGN_X_RIGHT)
		x = x - textWidth.x;

	draw_rect(x - 3, y, textWidth.x + 6, textWidth.y, color2);
	draw_string(string, x, y, color);
}

void visuals::drawing::draw_line(float x, float y, float x2, float y2, ImVec4 color, float thickness) {
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x, y), ImVec2(x2, y2), ImGui::GetColorU32(color), thickness);
}

void visuals::drawing::draw_2d_box(float x, float y, float w, float h, ImVec4 color, float thickness) {
	draw_line(x + (w / 2), y + h, x + (w / 2) - (w / 1), y + h, color, thickness);
	draw_line(x - (w / 2), y + h, x - (w / 2) + (w / 1), y + h, color, thickness);

	draw_line(x - (w / 2), y, x - (w / 2) + (w / 1), y, color, thickness);
	draw_line(x + (w / 2), y, x + (w / 2) - (w / 1), y, color, thickness);

	draw_line(x - (w / 2), y, x - (w / 2), y + (w / 1), color, thickness);
	draw_line(x + (w / 2), y, x + (w / 2), y + (w / 1), color, thickness);

	draw_line(x - (w / 2), y + h, x - (w / 2), y + h - (w / 1), color, thickness);
	draw_line(x + (w / 2), y + h, x + (w / 2), y + h - (w / 1), color, thickness);
}

void visuals::drawing::crosshair(float size, ImVec4 color) {
	float width, height = 0;

	width = (float)structs::screen->screen_width / 2.f;
	height = (float)structs::screen->screen_height / 2.f;

	/*draw_line(width, height - 45, width, height - 2, color, size);
	draw_line(width - 45, height, width - 2, height, color, size);
	draw_line(width + 45, height, width + 2, height, color, size);
	draw_line(width, height + 45, width, height + 2, color, size);*/

	/*draw_line(width, height - 12, width, height + 12, ImVec4(1, 1, 1, 1), 2);
	draw_line(width - 12, height, width + 12, height, ImVec4(1, 1, 1, 1), 2);*/

	draw_line(width + 35, height + 35, width - 35, height - 35, color, size);
	draw_line(width - 35, height + 35, width + 35, height - 35, color, size);
}

bool visuals::world_to_screen(structs::vector3 pos, structs::vector3& screen)
{
	structs::vector4 clipCoords;

	clipCoords.x = pos.x * globals::vars::engine::view_matrix[0] + pos.y * globals::vars::engine::view_matrix[4] + pos.z * globals::vars::engine::view_matrix[8] + globals::vars::engine::view_matrix[12];
	clipCoords.y = pos.x * globals::vars::engine::view_matrix[1] + pos.y * globals::vars::engine::view_matrix[5] + pos.z * globals::vars::engine::view_matrix[9] + globals::vars::engine::view_matrix[13];
	clipCoords.z = pos.x * globals::vars::engine::view_matrix[2] + pos.y * globals::vars::engine::view_matrix[6] + pos.z * globals::vars::engine::view_matrix[10] + globals::vars::engine::view_matrix[14];
	clipCoords.w = pos.x * globals::vars::engine::view_matrix[3] + pos.y * globals::vars::engine::view_matrix[7] + pos.z * globals::vars::engine::view_matrix[11] + globals::vars::engine::view_matrix[15];

	if (clipCoords.w < 0.1f) {
		return false;
	}

	structs::vector3 NDC{ clipCoords.x / clipCoords.w, clipCoords.y / clipCoords.w, clipCoords.z / clipCoords.w };

	screen.x = (structs::screen->screen_width / 2.0f) * (NDC.x + 1.0f);
	screen.y = (structs::screen->screen_height / 2.0f) * (1.0f - NDC.y); // Y is inverted in screen space

	return true;
}

void visuals::draw_visuals() {
	structs::player* enemy = nullptr;
	structs::vector3 feet_screen, head_screen;
	ImVec4 esp_colour{ 1, 1, 1, 1 };

	float center_x = structs::screen->screen_width / 2.f, center_y = structs::screen->screen_height / 2.f;

	for (int32_t i = 0; i < globals::vars::engine::player_count; i++) {
		enemy = structs::ent->ents[i];

		//if (functions::client::is_me(enemy) || functions::client::is_dead(enemy)) continue;

		functions::client::is_friend(enemy) ? esp_colour = globals::vars::imgui_colors::blue : esp_colour = globals::vars::imgui_colors::red;

		if (world_to_screen(enemy->root_origin, feet_screen) && world_to_screen(enemy->head_origin, head_screen)) {
			float width = fabs((head_screen.y - feet_screen.y) / 2.f);
			float height = width * 2;

		//	if(globals::vars::menu_settings::visuals::snap_lines)
				drawing::draw_line(center_x, structs::screen->screen_height, feet_screen.x, feet_screen.y, esp_colour, 1);
			
		//	if(globals::vars::menu_settings::visuals::box)
				drawing::draw_2d_box(head_screen.x, head_screen.y, width, height, esp_colour, 1);
			
			//if(globals::vars::menu_settings::visuals::names_distance)
				drawing::draw_text_shader(functions::utilites::va("%s - [ %.2f ]", enemy->name, structs::local_player->root_origin.get_distance(enemy->root_origin) / 100), head_screen.x, head_screen.y - 30, globals::vars::imgui_colors::white, globals::vars::imgui_colors::black, globals::vars::ALIGN_X_CENTER);

		}
	}
	drawing::crosshair(1, globals::vars::imgui_colors::light_blue);
}