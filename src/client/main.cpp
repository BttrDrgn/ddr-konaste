#include <main.hpp>

#include <utils/console/console.hpp>
#include <utils/exception/exception.hpp>
#include <utils/hook/hook.hpp>

#include <game/game.hpp>

namespace ddr
{
	utils::hook::detour message_box_a_hook;

	int message_box_a(HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
	{
		PRINT_DEBUG("\n----------\n%s\n\n%s\n----------", lpCaption, lpText);
		return message_box_a_hook.invoke<int>(hWnd, lpText, lpCaption, uType);
	}

	void init()
	{
		utils::exception::init("client");
		utils::console::init();

		PRINT_INFO("Loading DDRedux client...");
		PRINT_DEBUG("%s", GetCommandLineA());

		message_box_a_hook.create(&MessageBoxA, &message_box_a);

		game::init();
	}
}