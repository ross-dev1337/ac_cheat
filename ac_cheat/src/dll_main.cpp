#include "dll_main.h"

void hooks::init() {
	AllocConsole();
	SetConsoleTitle(L"ac_cheat");
	FILE* f = nullptr;
	freopen_s(&f, "CONOUT$", "w", stdout);

	printf("DLL - Loaded!\n");

	hooks::load_hooks();
}

bool APIENTRY DllMain(HANDLE h, int r, LPVOID lp) {
	switch (r) {
	case DLL_PROCESS_ATTACH:
		hooks::init();
		break;
	case DLL_PROCESS_DETACH:
		hooks::unload_hooks();
		break;
	}
	return true;
}