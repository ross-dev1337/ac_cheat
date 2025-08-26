#include "dll_main.h"

IMGUI_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace original_stub {
	decltype(&hooks::open_gl::wgl_swap_buffers) wgl_swap_buffers;
}

LRESULT hooks::wnd_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
	if (globals::vars::menu_settings::menu_open) {
		if (ImGui_ImplWin32_WndProcHandler(hwnd, umsg, wparam, lparam))
			return 0;

		switch (umsg) {
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_CHAR:
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
			return 0;
		}
	}
	return CallWindowProc(globals::vars::org_wndproc, hwnd, umsg, wparam, lparam);
}

bool hooks::open_gl::wgl_swap_buffers(HDC p1) {
	if (!globals::vars::run) {
		ImGui::CreateContext();

		ImGui_ImplWin32_Init(globals::vars::window);
		ImGui_ImplOpenGL2_Init();
		globals::vars::run = true; 
	}

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	 
	_interface::init_menu();
 

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	return original_stub::wgl_swap_buffers(p1);
}
 
void hooks::load_hooks() {
	if (MH_Initialize() == MH_OK) {
		printf("Hooks - Initialized!\n");

		globals::vars::window = FindWindow(L"SDL_app", L"AssaultCube");

		uint32_t wgl_swap_buffers = (uint32_t)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers");
		globals::vars::org_wndproc = (WNDPROC)SetWindowLongPtr(globals::vars::window, GWLP_WNDPROC, (LONG_PTR)hooks::wnd_proc);

		if (MH_CreateHook((void*)wgl_swap_buffers, (void**)hooks::open_gl::wgl_swap_buffers, (void**)&original_stub::wgl_swap_buffers) == MH_OK)
			printf("wgl_swap_buffers - Hooked!\n");
		else 
			printf("wgl_swap_buffers Failed to Hook!\n");

		if (MH_EnableHook(MH_ALL_HOOKS) == MH_OK)
			printf("Hooks - Enabled!\n");
		else
			printf("Hooks failed to enable!\n");
	}
	else {
		printf("Hooks - Failed to Initialize!\n");
	}
}

void hooks::unload_hooks() {
	if (MH_Uninitialize() == MH_OK) {
		printf("Hooks - Uninitialized!\n");

		MH_DisableHook(MH_ALL_HOOKS);
	}
	else {
		printf("Hooks Failed to Uninitialize!");
	}	
}