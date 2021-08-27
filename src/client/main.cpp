#include <main.hpp>

#include <utils/console/console.hpp>
#include <utils/exception/exception.hpp>
#include <utils/hook/hook.hpp>

#include <game/game.hpp>

namespace ddr
{
	void init()
	{
		utils::exception::init("client");
		utils::console::init();

		PRINT_INFO("Loading DDRedux client...");
		game::init();
	}
}

bool __stdcall DllMain(::HMODULE, ::DWORD reason, ::LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		ddr::init();

		return true;
	}

	return false;
}
