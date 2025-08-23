#include "dll_main.h"

namespace original_stub {
	decltype(&hooks::open_gl::wgl_swap_buffers) wgl_swap_buffers;
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
	ImGui::End();

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