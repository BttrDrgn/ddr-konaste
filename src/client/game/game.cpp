#include <game/game.hpp>
#include <game/discord/discord.hpp>
#include <game/window/window.hpp>
#include <game/core/core.hpp>
#include <game/directx/directx.hpp>
#include <callbacks/callbacks.hpp>

namespace ddr
{
	void game::init()
	{
		callbacks::init();
		core::init();
		drpc::init();
		window::init();
		directx::init();

		PRINT_INFO("Game initialized.");
	}
}
