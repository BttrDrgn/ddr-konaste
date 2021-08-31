#pragma once

namespace ddr::game
{
	class input final
	{
		public:
			enum callback_type : std::uint8_t
			{
				on_key_down,
				on_key_up,
			};

			enum result_type : std::uint8_t
			{
				cont,
				interrupt,
			};

			using callback = input::result_type(__cdecl*)(std::uint32_t);

			static void init();
			static void on(input::callback_type type, input::callback callback);

			static bool is_key_down(std::uint32_t key);
			static LRESULT __stdcall wnd_proc_hook(const HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);


		private:
			static std::unordered_map<input::callback_type, std::vector<input::callback>> callbacks_;
	};
}
