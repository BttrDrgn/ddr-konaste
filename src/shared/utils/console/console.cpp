#include <utils/console/console.hpp>

namespace utils
{
	void console::init()
	{
		console::file_ = std::fopen("..\\ddredux\\logs\\console.log", "ab");

		::AllocConsole();
		::SetConsoleTitleA("DDR Console");

		std::freopen("CONOUT$", "w", stdout);
		std::freopen("CONIN$", "r", stdin);
	}

	::_iobuf* console::file()
	{
		return console::file_;
	}

	::_iobuf* console::file_;
}
