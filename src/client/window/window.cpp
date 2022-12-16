#include <utils/format/format.hpp>
#include <utils/char_conversion/char_conversion.hpp>

#include <window/window.hpp>

::HWND window::hwnd = 0;
::WNDPROC window::wnd_proc = 0;

utils::hook::detour create_window_ex_w_hook;
::HWND create_window_ex_w(
	::DWORD     dwExStyle,
	::LPCWSTR   lpClassName,
	::LPCWSTR   lpWindowName,
	::DWORD     dwStyle,
	int       X,
	int       Y,
	int       nWidth,
	int       nHeight,
	::HWND      hWndParent,
	::HMENU     hMenu,
	::HINSTANCE hInstance,
	::LPVOID    lpParam
)
{
	//if (!lstrcmpW(lpWindowName, L"DanceDanceRevolution"))
	//{
	//	lpWindowName = utils::char_conversion::widen_char(&utils::format::va("DDR | r%i", VERSION)[0]);
	//	window::hwnd = create_window_ex_w_hook.invoke<::HWND>(dwExStyle, lpClassName, lpWindowName,
	//		dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);

	//	return window::hwnd;
	//}

	return create_window_ex_w_hook.invoke<::HWND>(dwExStyle, lpClassName, lpWindowName,
		dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

utils::hook::detour message_box_a_hook;
int message_box_a(::HWND hWnd, ::LPCSTR lpText, ::LPCSTR lpCaption, ::UINT uType)
{
	PRINT_DEBUG("0x1%x", _ReturnAddress());
	PRINT_ERROR("\n----------\n%s\n\n%s\n----------", lpCaption, lpText);
	return message_box_a_hook.invoke<int>(hWnd, lpText, lpCaption, uType);
}

utils::hook::detour set_foreground_hook;
bool set_foreground(::HWND)
{
	return false;
}

void window::init()
{
	create_window_ex_w_hook.create(&CreateWindowExW, &create_window_ex_w);
	message_box_a_hook.create(&MessageBoxA, &message_box_a);
	set_foreground_hook.create(&SetForegroundWindow, &set_foreground);
}