#include <game/game.hpp>
#include <game/core/core.hpp>


namespace ddr
{
	utils::hook::detour sub_14000D620_hook;

	std::int64_t sub_14000D620(std::int64_t a1)
	{
		PRINT_DEBUG("0x1%x", _ReturnAddress());
		return sub_14000D620_hook.invoke<std::int64_t>(a1);
	}

	void core::init()
	{
		sub_14000D620_hook.create(0x14000D620, &sub_14000D620);
	}
}
