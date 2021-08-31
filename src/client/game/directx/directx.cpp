#include <game/directx/directx.hpp>
#include <game/directx/defs.h>
#include <game/window/window.hpp>

#include <utils/format/format.hpp>

namespace ddr::game
{
	std::uint64_t* directx::methods_table;
	::WNDCLASSEX directx::wnd_class;
	::HWND directx::hwnd;

	void directx::detour(uint16_t index, void** orig, void* function)
	{
		assert(index >= 0 && orig != NULL && function != NULL);
		void* target = (void*)directx::methods_table[index];

		MH_CreateHook(target, function, orig);
		MH_EnableHook(target);
	}

	HRESULT __stdcall end_scene_hook(IDirect3DDevice9* pD3D9)
	{
		static bool init = false;
		if (!init)
		{
			init = true;

			IMGUI_CHECKVERSION();

			ImGui::CreateContext();

			if (window::hwnd == 0)
			{
				window::hwnd = FindWindowA(NULL, &utils::format::va("DDRedux | r%i", VERSION)[0]);
			}

			//window::wnd_proc = (WNDPROC)SetWindowLongPtrA(window::hwnd, GWLP_WNDPROC, (LONG_PTR)input::wnd_proc_hook);

			ImGui_ImplWin32_Init(window::hwnd);
			ImGui_ImplDX9_Init(pD3D9);
		}

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::GetIO().MouseDrawCursor = true;
		ImGui::ShowDemoWindow();

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

		return end_scene(pD3D9);
	}

	void directx::init()
	{
		directx::wnd_class.cbSize = sizeof(WNDCLASSEX);
		directx::wnd_class.style = CS_HREDRAW | CS_VREDRAW;
		directx::wnd_class.lpfnWndProc = DefWindowProcA;
		directx::wnd_class.cbClsExtra = 0;
		directx::wnd_class.cbWndExtra = 0;
		directx::wnd_class.hInstance = GetModuleHandleA(0);
		directx::wnd_class.hIcon = 0;
		directx::wnd_class.hCursor = 0;
		directx::wnd_class.hbrBackground = 0;
		directx::wnd_class.lpszMenuName = 0;
		directx::wnd_class.lpszClassName = "DDRedux";
		directx::wnd_class.hIconSm = 0;
		RegisterClassExA(&directx::wnd_class);
		directx::hwnd = CreateWindowA(directx::wnd_class.lpszClassName, "DXWIN", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, 0, 0, directx::wnd_class.hInstance, 0);

		HMODULE D3D9Module = GetModuleHandleA("d3d9.dll");

		void* d3d_create = GetProcAddress(D3D9Module, "Direct3DCreate9");

		LPDIRECT3D9 d3d = ((LPDIRECT3D9(__stdcall*)(uint32_t))(d3d_create))(D3D_SDK_VERSION);

		D3DDISPLAYMODE dp_mode;
		d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dp_mode);

		D3DPRESENT_PARAMETERS params;
		params.BackBufferWidth = 0;
		params.BackBufferHeight = 0;
		params.BackBufferFormat = dp_mode.Format;
		params.BackBufferCount = 0;
		params.MultiSampleType = D3DMULTISAMPLE_NONE;
		params.MultiSampleQuality = 0;
		params.SwapEffect = D3DSWAPEFFECT_DISCARD;
		params.hDeviceWindow = directx::hwnd;
		params.Windowed = 1;
		params.EnableAutoDepthStencil = 0;
		params.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
		params.Flags = 0;
		params.FullScreen_RefreshRateInHz = 0;
		params.PresentationInterval = 0;

		LPDIRECT3DDEVICE9 d3ddev;
		d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, directx::hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT, &params, &d3ddev);

		directx::methods_table = (std::uint64_t*)::calloc(119, sizeof(std::uint64_t));
		memcpy(directx::methods_table, *(std::uint64_t**)d3ddev, 119 * sizeof(std::uint64_t));

		directx::detour(42, (void**)&end_scene, end_scene_hook);
	}
}