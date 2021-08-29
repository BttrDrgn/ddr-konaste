#include <utils/console/console.hpp>
#include <utils/hook/hook.hpp>
#include <utils/format/format.hpp>

#include <game/game.hpp>
#include <game/directx/directx.hpp>
#include <game/window/window.hpp>

#include <MinHook.h>

typedef HRESULT(APIENTRY* EndScene) (LPDIRECT3DDEVICE9);
HRESULT APIENTRY EndScene_hook(LPDIRECT3DDEVICE9);
EndScene EndScene_orig = 0;

namespace ddr
{
	HRESULT APIENTRY EndScene_hook(LPDIRECT3DDEVICE9 pD3D9)
	{
		static bool init = false;

		if (!init)
		{
			PRINT_DEBUG("%x", _ReturnAddress());
			init = true;

			window::hwnd = FindWindowA(NULL, &utils::format::va("DDRedux | r%i", VERSION)[0]);
			//window::wnd_proc = (WNDPROC)SetWindowLongPtrA(window::hwnd, GWL_WNDPROC, (LONG_PTR)input::wnd_proc_proxy);

			IMGUI_CHECKVERSION();

			ImGui::CreateContext();

			ImGuiIO& io = ImGui::GetIO();

			io.IniFilename = "menus.ini";

			io.MouseDrawCursor = true;

			ImGui_ImplWin32_Init(window::hwnd);
			ImGui_ImplDX9_Init(pD3D9);
		}

		ImGui::ShowDemoWindow();

		/*
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::EndFrame();
		ImGui::Render();
		*/

		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

		return EndScene_orig(pD3D9);
	}

	void directx::init()
	{

	}
}
