#pragma once

namespace globals::vars {
	extern HWND window;
	extern bool run;

	namespace menu_settings {
		extern bool menu_open;

		namespace aimbot {
			extern bool enable_aimbot, vis_check;
		}

		namespace visuals {
			extern bool snap_lines, names_distance, box;
		}
	}
}