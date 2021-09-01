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
			//rewrite this to write please drgn
			utils::hook::set(0x1400B331F, 0x48);
			utils::hook::set(0x1400B331F+1, 0x31);
			utils::hook::set(0x1400B331F+2, 0xC0); //XOR RAX,RAX
			utils::hook::set(0x1400B331F+3, 0x48);
			utils::hook::set(0x1400B331F+4, 0xFF);
			utils::hook::set(0x1400B331F+5, 0xC0); //INC RAX
			
		}
		else //if the user descides to disable it
		{
			utils::hook::set(0x1400B331F, 0x48);
			utils::hook::set(0x1400B331F+1, 0x31);
			utils::hook::set(0x1400B331F+2, 0xC0); //XOR RAX,RAX
			utils::hook::nop(0x1400B3322, 3);
		}
	}
}
