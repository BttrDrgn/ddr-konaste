#include <main.hpp>

#include <utils/nt/nt.hpp>

#include <core/core.hpp>
#include <window/window.hpp>

void init()
{
	//Check if attached to ddr-konaste.exe and compare version info
	if (GetModuleHandleA("ddr-konaste.exe") != nullptr && !strcmp("VGP:J:A:A:2022112900", reinterpret_cast<char*>(0x00000001402B5A38)))
	{
		utils::console::init();

		SetCurrentDirectoryA("..\\");

		core::init();
		window::init();
	}
	else
	{
		utils::nt::error(
			"DDR",

			"The game that DDR has been attached to is not DanceDanceRevolution Konaste Version 2022112900!!!"
			"\n\n!!Please install to the correct directory !!"
			"\n\nEx: C:\\Games\\DanceDanceRevolution\\game\\modules\\"
		);
	}
}
