#include "dll_main.h"

namespace globals::vars {
	HWND window = 0;
	bool run = false;
	WNDPROC org_wndproc = nullptr; 

	namespace menu_settings {
		bool menu_open = false;

		namespace aimbot { 
			bool enable_aimbot, vis_check;
		}

		namespace visuals {
			bool snap_lines, names_distance, box;
		}
	}
}