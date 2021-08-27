#include <utils/console/console.hpp>
#include <utils/hook/hook.hpp>
#include <utils/format/format.hpp>

#include <game/game.hpp>
#include <game/window/window.hpp>


namespace ddr
{
	::HWND window::hwnd = 0;
	::WNDPROC window::wnd_proc = 0;

	void window::init()
	{

	}
}
