#include <game/game.hpp>
#include <game/discord/discord.hpp>
#include <game/window/window.hpp>
#include <game/core/core.hpp>
#include <game/directx/directx.hpp>
#include <game/callbacks/callbacks.hpp>

namespace ddr
{
	void game::init()
	{
		callbacks::init();
		core::init();
		drpc::init();
		window::init();

		callbacks::on(callbacks::type::window_create, []()
		{
			directx::init();
		});

		PRINT_INFO("Game initialized.");
	}
}
