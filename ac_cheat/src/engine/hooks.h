#pragma once

namespace hooks {
	void init();
	void load_hooks();
	void unload_hooks();
	LRESULT wnd_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

	namespace open_gl {
		bool wgl_swap_buffers(HDC p1);
	}
} 