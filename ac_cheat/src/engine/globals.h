#pragma once

namespace globals::vars {
	extern HWND window;
	extern bool run;
	extern WNDPROC org_wndproc;
	extern uint32_t module_base;

	namespace engine {
		extern uint32_t player_count;
		extern float* view_matrix; 
	}

	namespace menu_settings {
		extern bool menu_open;

		namespace aimbot {
			extern bool enable_aimbot, vis_check;
		}

		namespace visuals {
			extern bool snap_lines, names_distance, box; 
		}
	}

	namespace imgui_colors {
		extern ImVec4 blue;
		extern ImVec4 light_blue;
		extern ImVec4 red;
		extern ImVec4 white;
		extern ImVec4 black;
		extern ImVec4 green;
		extern ImVec4 yellow;
	}

	enum align {
		ALIGN_X_LEFT = 1 << 1,
		ALIGN_X_CENTER = 1 << 2,
		ALIGN_X_RIGHT = 1 << 3,
	};
}