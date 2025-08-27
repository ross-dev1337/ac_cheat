#pragma once

namespace functions {
	namespace engine {
		void update_ponters();
	}

	namespace client {
		bool is_me(structs::player* ent);
		bool is_dead(structs::player* ent);
		bool is_friend(structs::player* ent);
	}
	namespace SDL2 {
		int SDL_SetRelativeMouseMove(int mode);
	}

	namespace utilites {
		const char* va(const char* fmt, ...); 
	}
} 