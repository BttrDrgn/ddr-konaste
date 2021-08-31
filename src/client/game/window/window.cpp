#include <utils/format/format.hpp>
#include <utils/char_conversion/char_conversion.hpp>

#include <game/game.hpp>
#include <game/window/window.hpp>


namespace ddr::game
{
	::HWND window::hwnd = 0;
	::WNDPROC window::wnd_proc = 0;

	utils::hook::detour create_window_ex_w_hook;
	utils::hook::detour message_box_a_hook;
	utils::hook::detour throw_error_dialog_hook;

	HWND create_window_ex_w(
		DWORD     dwExStyle,
		LPCWSTR   lpClassName,
		LPCWSTR   lpWindowName,
		DWORD     dwStyle,
		int       X,
		int       Y,
		int       nWidth,
		int       nHeight,
		HWND      hWndParent,
		HMENU     hMenu,
		HINSTANCE hInstance,
		LPVOID    lpParam
	)
	{
		if (!lstrcmpW(lpWindowName, L"DanceDanceRevolution"))
		{
			lpWindowName = utils::char_conversion::widen_char(&utils::format::va("DDRedux | r%i", VERSION)[0]);
			window::hwnd = create_window_ex_w_hook.invoke<HWND>(dwExStyle, lpClassName, lpWindowName,
				dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);

			return window::hwnd;
		}

		return create_window_ex_w_hook.invoke<HWND>(dwExStyle, lpClassName, lpWindowName,
			dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	}

	int message_box_a(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
	{
		PRINT_ERROR("\n----------\n%s\n\n%s\n----------", lpCaption, lpText);
		return message_box_a_hook.invoke<int>(hWnd, lpText, lpCaption, uType);
	}

	void throw_error_dialog(unsigned int a1, int a2, const char* a3, const char* a4)
	{
		PRINT_DEBUG("0x1%x", _ReturnAddress());
		std::string temp = a3;
		if (temp.find("Code : 0x199") != std::string::npos)
		{
			a3 = "Unable to authenticate to the Konami Konaste servers\n\nCode : 0x199";
		}

		return throw_error_dialog_hook.invoke<void>(a1, a2, a3, a4);
	}

	void window::init()
	{
		create_window_ex_w_hook.create(&CreateWindowExW, &create_window_ex_w);
		message_box_a_hook.create(&MessageBoxA, &message_box_a);
		throw_error_dialog_hook.create(0x140010AE0, throw_error_dialog);
	}
}
