#include "graphics.hpp"

#include "imgui/imgui.h"
#include "imgui_impl_source.hpp"

extern void graphics_start_platform();

void graphics::start() {
	graphics_start_platform();
}