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

			window::hwnd = FindWindowA(NULL, &utils::format::va("PlayRemedy | r%i", VERSION)[0]);
			//window::wnd_proc = (WNDPROC)SetWindowLongPtrA(window::hwnd, GWL_WNDPROC, (LONG_PTR)input::wnd_proc_proxy);

			IMGUI_CHECKVERSION();

			ImGui::CreateContext();

			ImGuiIO& io = ImGui::GetIO();

			io.IniFilename = "menus.ini";

			io.MouseDrawCursor = true;

			//ImGui_ImplWin32_Init(window::hwnd);
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
		PRINT_INFO("Starting DirectX hook...");
		while (GetModuleHandle("d3d9.dll") == 0)
		{
			Sleep(16);
		}

		PRINT_INFO("D3D9 loaded...");

		HMODULE hmod = 0;

		LPDIRECT3D9 d3d = 0;
		LPDIRECT3DDEVICE9 d3ddev = 0;

		auto temp = CreateWindowA("BUTTON", "Temp Window", WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, NULL, NULL, hmod, NULL);
		if (!temp)
		{
			PRINT_ERROR("Error creating temp window!");
		}

		d3d = Direct3DCreate9(D3D_SDK_VERSION);
		if (!d3d)
		{
			PRINT_ERROR("Error creating D3D9! Destroying temp...");
			DestroyWindow(temp);
		}

		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = temp;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

		HRESULT result = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, temp, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);
		if (result != D3D_OK)
		{
			PRINT_ERROR("Error! Result not ok. Destroying D3D9 and temp...");
			d3d->Release();
			DestroyWindow(temp);
		}

		DWORD* vtable = (DWORD*)d3ddev;
		vtable = (DWORD*)vtable[0];

		//EndScene_orig = (EndScene)vtable[42];

		//MH_CreateHook((DWORD_PTR*)vtable[42], &EndScene_hook, reinterpret_cast<void**>(&EndScene_orig));
		//MH_EnableHook((DWORD_PTR*)vtable[42]);

		d3ddev->Release();
		d3d->Release();
		DestroyWindow(temp);
	}
}
