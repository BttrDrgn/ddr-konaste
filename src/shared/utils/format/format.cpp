

#include <utils/format/format.hpp>

namespace utils
{
	std::string format::va(const char* fmt, ...)
	{
		auto va = ::va_list();

		va_start(va, fmt);

		char result[512]{};

		std::vsprintf(result, fmt, va);

		return std::string(result);
	}

	std::string format::replace(const std::string& orig, const std::string& fnd, const std::string& repl)
	{
		std::string ret = orig;
		size_t pos = 0;
		while (true)
		{
			pos = ret.find(fnd, pos);
			if (pos == std::string::npos) break;

			ret.replace(pos, pos + fnd.size(), repl);
			pos += repl.size();
		}
		return ret;
	}
}
