#include "ui.hpp"
#include "mem/module.hpp"
#include "graphics/graphics.hpp"

/* Set theme */
void ui_init() {
}

/* Draw */
void ui_draw() {
	ImGui::Begin("Kisak");

	if (ImGui::Button("Unload")) {
		mem::unload_self();
	}

	ImGui::End();
}
