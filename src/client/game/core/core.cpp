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

		//Show Fast/Slow judgement in-game
		if (true) //Placeholder, tell ImGui to disable/enable it in options.
		{
			utils::hook::write_bytes(0x00000001400B331F, { 0x48, 0x31, 0xC0, 0x48, 0xFF, 0xC0 });
			
		}
		else //if the user descides to disable it
		{
			utils::hook::write_bytes(0x00000001400B331F, { 0x48, 0x31, 0xC0, 0x90, 0x90, 0x90 });
		}
	}
}
