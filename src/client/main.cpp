#include <main.hpp>

#include <utils/exception/exception.hpp>
#include <utils/nt/nt.hpp>
#include <utils/file_system/file_system.hpp>

#include <game/game.hpp>

namespace ddr
{
	void init()
	{
		//Check if attached to ddr-konaste.exe and compare version info
		if (GetModuleHandleA("ddr-konaste.exe") != nullptr && !strcmp("VGP:J:A:A:2021082401", reinterpret_cast<char*>(0x00000001401B56A8)))
		{
			utils::console::init();
			utils::file_system::init();
			utils::exception::init("client");

			PRINT_INFO("Loading DDRedux client...");
			SetCurrentDirectoryA("..\\");

			game::init();
		}
		else
		{
			utils::nt::error(
				"DDRedux",

				"The game that DDRedux has been attached to is not DanceDanceRevolution Konaste Open Alpha!!!"
				"\n\n!!Please install to the correct directory !!"
				"\n\nEx: C:\\Games\\DanceDanceRevolution\\game\\modules\\"
			);
		}
	}
}