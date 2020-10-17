#include "graphics.hpp"
#include "kdebug.hpp"
#include "gamemodule.hpp"
#include "gamedata.hpp"
#include "mem/hook.hpp"
#include "cxxutil.hpp"
#include "ui.hpp"

#include "imgui/imgui_impl_dx9.h"
#include "imgui_impl_source.hpp"

#include <Windows.h>
#include <d3d9.h>

using Present_t = HRESULT(__stdcall*)(IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*);

static std::unique_ptr<mem::VTableHook> present_hook;

namespace hooks {

	/* Called to display the back buffer */
	static HRESULT __stdcall present(IDirect3DDevice9* device, const RECT* src, const RECT* dest, HWND override, const RGNDATA* dirty) {
		run_static {
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();

			ImGui_ImplSource_Init();
			ImGui_ImplDX9_Init(device);

			ui_init();
		};

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplSource_NewFrame();
		ImGui::NewFrame();

		ui_draw();

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

		/* Call the original function */
		static auto original = (Present_t)present_hook->get_real(17);
		return original(device, src, dest, override, dirty);
	}

}

void graphics_hook_platform() {
	/* d3d9 device: FF 75 FC 8B 0D ? ? ? ? in shaderapidx9.dll */
	auto device_ptr = gamemodule::shaderapi.scan(GD_PAT_D3DDEVICE);
	K_ASSERT(device_ptr);

	IDirect3DDevice9* device = **(IDirect3DDevice9***)(device_ptr + 0x5);
	K_LOG("IDirect3DDevice9: %p\n", (void*)device);

	present_hook = std::make_unique<mem::VTableHook>((mem::vtable*)device);
	present_hook->replace(17, (std::uintptr_t)hooks::present);
}
