#include <game/game.hpp>
#include <game/core/core.hpp>


namespace ddr::game
{
	void core::init()
	{
		//Skips 2 auth checks
		utils::hook::nop(0x000000014000D76B, 6);
		utils::hook::nop(0x000000014000D832, 6);
	}
}
