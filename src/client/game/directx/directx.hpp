#pragma once

#include <d3d9.h>

#include <MinHook.h>

namespace ddr::game
{
	class directx final
	{
	public:
		static void init();

		static void detour(uint16_t index, void** orig, void* function);

		static std::uint64_t* methods_table;

		static ::WNDCLASSEX wnd_class;
		static ::HWND hwnd;
	};
}