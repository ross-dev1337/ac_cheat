#pragma once

namespace hooks {
	void init();
	void load_hooks();
	void unload_hooks();

	namespace open_gl {
		bool wgl_swap_buffers(HDC p1);
	}
}