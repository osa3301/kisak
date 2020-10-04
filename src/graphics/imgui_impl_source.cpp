#include "imgui_impl_source.hpp"
#include "imgui/imgui.h"
#include "iface.hpp"
#include "kdebug.hpp"

void ImGui_ImplSource_Init() {
	ImGuiIO& io = ImGui::GetIO();
	io.BackendPlatformName = "source_engine";
}

void ImGui_ImplSource_NewFrame() {
	ImGuiIO& io = ImGui::GetIO();

	int width, height;
	iface::engine->get_screen_size(width, height);
	K_ASSERT(width > 0 && height > 0);

	io.DisplaySize = ImVec2((float)width, (float)height);
	io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

	/* Mouse */
	io.MouseDown[0] = iface::input->is_button_down(sdk::ButtonCode::MOUSE_LEFT);
	io.MouseDown[1] = iface::input->is_button_down(sdk::ButtonCode::MOUSE_RIGHT);
	io.MouseDown[2] = iface::input->is_button_down(sdk::ButtonCode::MOUSE_MIDDLE);

	int mouse_x = iface::input->get_analog_value(sdk::AnalogCode::MOUSE_X);
	int mouse_y = iface::input->get_analog_value(sdk::AnalogCode::MOUSE_Y);

	io.MousePos = ImVec2((float)mouse_x, (float)mouse_y);
}