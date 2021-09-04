#pragma once
#include "stdafx.hpp"

namespace ddr::game
{
	class core final
	{
    public:
        static void init();

		static float frame_rate;
		static bool judegment;
		static char name[9];
	};
}
