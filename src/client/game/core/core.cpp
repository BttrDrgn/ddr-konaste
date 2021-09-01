#include <game/game.hpp>
#include <game/core/core.hpp>

#include <callbacks/callbacks.hpp>


namespace ddr::game
{
	float core::frame_rate;
	bool core::judegment;

	utils::hook::detour debugger_present_hook;
	bool debugger_present()
	{
		return false;
	}

	utils::hook::detour exit_process_hook;
	void exit_process(::UINT)
	{
		return;
	}

	void core::init()
	{
		core::frame_rate = 0.0f;
		core::judegment = false;

		//Skips 2 auth checks
		utils::hook::nop(0x000000014000D76B, 6);
		utils::hook::nop(0x000000014000D832, 6);

		//Disable IsDebuggerPresent from exiting process
		utils::hook::nop(0x000000014001D81C, 5);

		debugger_present_hook.create(&::IsDebuggerPresent, &debugger_present);
		//exit_process_hook.create(&::ExitProcess, &exit_process);

		callbacks::on(callbacks::type::settings_saved, []
		{
			//Judegment update
			if (core::judegment)
			{
				utils::hook::write_bytes(0x00000001400B331F, { 0x48, 0x31, 0xC0, 0x48, 0xFF, 0xC0 });
			}
			else
			{
				utils::hook::write_bytes(0x00000001400B331F, { 0x48, 0x31, 0xC0, 0x90, 0x90, 0x90 });
			}
		});
	}
}
