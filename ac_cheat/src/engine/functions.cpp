#include "dll_main.h"

int functions::SDL2::SDL_SetRelativeMouseMove(int mode) {
	int address = (int)GetProcAddress(GetModuleHandle(L"SDL2.dll"), "SDL_SetRelativeMouseMode");
	return call<int>(address, mode);
}