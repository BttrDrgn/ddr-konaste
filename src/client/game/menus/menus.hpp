#pragma once

namespace ddr::game
{
	class menus final
	{
	public:
		static void init();
		static void update();

		static bool active;

		class states final
		{
		public:
			static bool diag;
		};

	private:
		static ImGuiIO& io;
		static ImGuiStyle& s;
	};
}