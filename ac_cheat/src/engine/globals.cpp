#include "dll_main.h"

namespace globals::vars {
	HWND window = 0;
	bool run = false;
	WNDPROC org_wndproc = nullptr; 
	uint32_t module_base = 0;

	namespace engine {
		uint32_t player_count = 0;
		float* view_matrix = nullptr;
	}

	namespace menu_settings {
		bool menu_open = false;

		namespace aimbot { 
			bool enable_aimbot, vis_check;
		}

		namespace visuals {
			bool snap_lines, names_distance, box;
		}
	}

	namespace imgui_colors {
		ImVec4 blue = { 0.f, .3f, .9f, 1 };
		ImVec4 light_blue = { .1f, .5f, 1, 1 };
		ImVec4 red = { 1, 0, 0, 1 };
		ImVec4 white = { 1, 1, 1, 1 };
		ImVec4 black = { 0.f, 0.f, 0.f, 0.5f };
		ImVec4 green = { 0, .8f, .1f, 1 };
		ImVec4 yellow = { .9f, .9f, .1f, 1 };
	}
}