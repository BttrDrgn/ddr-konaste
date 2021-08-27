#include <utils/console/console.hpp>
#include <utils/hook/hook.hpp>
#include <utils/format/format.hpp>
#include <utils/char_conversion/char_conversion.hpp>

#include <game/game.hpp>
#include <game/window/window.hpp>


namespace ddr
{
	::HWND window::hwnd = 0;
	::WNDPROC window::wnd_proc = 0;

	utils::hook::detour create_window_ex_w_hook;

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
		}

		return create_window_ex_w_hook.invoke<HWND>(dwExStyle, lpClassName, lpWindowName,
			dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	}

	void window::init()
	{
		create_window_ex_w_hook.create(&CreateWindowExW, &create_window_ex_w);
	}
}
