#include <utils/console/console.hpp>
#include <utils/hook/hook.hpp>
#include <utils/file_system/file_system.hpp>
#include <utils/nt/nt.hpp>

#include <game/game.hpp>
#include <game/discord/discord.hpp>
#include <game/window/window.hpp>
#include <game/directx/directx.hpp>

namespace ddr
{
	void game::init()
	{
		drpc::init();
		window::init();
		//directx::init();
		PRINT_INFO("Game initialized.");
	}
}
