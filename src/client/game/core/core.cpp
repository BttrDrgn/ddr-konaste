#include <game/game.hpp>
#include <game/core/core.hpp>


namespace ddr::game
{
	float core::frame_rate;

	void core::init()
	{
		core::frame_rate = 0.0f;

		//Skips 2 auth checks
		utils::hook::nop(0x000000014000D76B, 6);
		utils::hook::nop(0x000000014000D832, 6);

		//Disable IsDebuggerPresent from exiting process
		utils::hook::nop(0x000000014001D81C, 5);
	}
}
