#pragma once

namespace ddr
{
	class callbacks final
	{
	public:
		enum class type : std::uint32_t
		{
			main_loop,

			settings_saved,
			settings_reset,
		};
		
		static void init();

		static void on(callbacks::type type, utils::callback<void __cdecl()> callback);
		static void on(const std::initializer_list<callbacks::type>& types, utils::callback<void __cdecl()> callback);

		static void once(utils::callback<void __cdecl()> callback);
		static void run_basic_callbacks(callbacks::type type);

	private:

		static std::mutex mtx_;
		static std::vector<utils::callback<void __cdecl()>> once_callbacks_;
		
		static std::unordered_map<callbacks::type, std::vector<utils::callback<void __cdecl()>>> basic_callbacks_;
	};
}