#include "dll_main.h"

void functions::engine::update_ponters() {
	structs::local_player = *(structs::player**)(globals::vars::module_base + 0x0018AC00);
	structs::ent = *(structs::entity**)(globals::vars::module_base + 0x0018AC04);
	structs::screen = (structs::screen_dimensions*)(globals::vars::module_base + 0x00191ED8);


	globals::vars::engine::player_count = *(int*)(globals::vars::module_base + 0x18AC0C);
	globals::vars::engine::view_matrix = (float*)(globals::vars::module_base + 0x17DFD0);
}

bool functions::client::is_me(structs::player* ent) {
	return ent == structs::local_player;
}

bool functions::client::is_dead(structs::player* ent) {
	return ent->current_health < 0 || ent->current_health > 100;
}

bool functions::client::is_friend(structs::player* ent) {
	return ent->team == structs::local_player->team;
}


int functions::SDL2::SDL_SetRelativeMouseMove(int mode) {
	int address = (int)GetProcAddress(GetModuleHandle(L"SDL2.dll"), "SDL_SetRelativeMouseMode");
	return call<int>(address, mode); 
}

const char* functions::utilites::va(const char* fmt, ...) {
	char* buffer = new char[0x200];

	memset(buffer, 0, 0x200);
	va_list va_l;
	va_start(va_l, fmt);
	vsnprintf(buffer, 0x200, fmt, va_l);
	va_end(va_l);

	return buffer;
}

