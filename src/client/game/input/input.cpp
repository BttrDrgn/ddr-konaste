#include <utils/console/console.hpp>
#include <utils/hook/hook.hpp>

#include <game/input/input.hpp>
#include <game/window/window.hpp>
#include <game/menus/menus.hpp>

namespace ddr::game
{
	std::unordered_map<input::callback_type, std::vector<input::callback>> input::callbacks_;

	void input::init()
	{
		input::on(input::callback_type::on_key_down, [](auto key) -> input::result_type
		{
			//F1
			if (key == 112)
			{
				menus::states::shortcuts = !menus::states::shortcuts;
				return input::result_type::interrupt;
			}

			//F3
			if(key == 114)
			{
				menus::active = !menus::active;
				return input::result_type::interrupt;
			}

			//F12
			if (key == 123)
			{
				menus::states::diag = !menus::states::diag;
				return input::result_type::interrupt;
			}

			return input::result_type::cont;
		});
	}

	void input::on(input::callback_type type, input::callback callback)
	{
		input::callbacks_[type].emplace_back(callback);
	}

	bool input::is_key_down(std::uint32_t key)
	{
		return ImGui::IsKeyPressed(key, false);
	}

	LRESULT __stdcall input::wnd_proc_hook(const HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
	{

		switch (message)
		{
		case WM_KEYDOWN:

			for (const auto callback : input::callbacks_[callback_type::on_key_down])
			{
				callback(wparam);
			}

			break;

		case WM_KEYUP:

			for (const auto callback : input::callbacks_[callback_type::on_key_up])
			{
				callback(wparam);
			}

			break;

		case WM_SYSCOMMAND:
			if ((wparam & 0xFF00) == SC_KEYMENU)
			{
				return 1;
			}
		}

		if (::ImGui_ImplWin32_WndProcHandler(hwnd, message, wparam, lparam))
		{
			return true;
		}

		return ::CallWindowProcA(window::wnd_proc, hwnd, message, wparam, lparam);
	}
}
