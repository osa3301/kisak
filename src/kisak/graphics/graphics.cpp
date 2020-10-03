#include "graphics.hpp"

#include "imgui.h"

extern void graphics_init_platform();

/* Initialize graphics hooks and contexts */
void graphics_init() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	graphics_init_platform();
}

