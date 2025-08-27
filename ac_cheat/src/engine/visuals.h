#pragma once

namespace visuals {
	bool world_to_screen(structs::vector3 pos, structs::vector3& screen);
	void draw_visuals();

	namespace drawing {
		void draw_text(const char* text, float x, float y, ImVec4 color, bool is_outlined, ImVec4 outlined_color);
		void draw_rect(float x, float y, float width, float height, ImVec4 color);
		void draw_string(const char* string, float x, float y, ImVec4 color); 
		void draw_text_shader(const char* string, float x, float y, ImVec4 color, ImVec4 color2, globals::vars::align op);
		void draw_line(float x, float y, float x2, float y2, ImVec4 color, float thickness);
		void draw_2d_box(float x, float y, float w, float h, ImVec4 color, float thickness);
		void crosshair(float size, ImVec4 color); 	
	}
}