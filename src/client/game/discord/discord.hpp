#pragma once
#include "stdafx.hpp"
#include <discord.h>

namespace ddr
{
	class drpc final
	{
    public:
        static void init();

		static void update();

		static void change_status(const std::string& text);
		static void change_large_image(const char* image, const char* text);
		static void change_small_image(const std::string& image, const std::string& text);
	};
}
