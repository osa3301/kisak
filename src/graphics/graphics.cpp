#include "graphics.hpp"

#include "imgui/imgui.h"
#include "imgui_impl_source.hpp"

extern void graphics_hook_platform();

void graphics::hook() {
	graphics_hook_platform();
}