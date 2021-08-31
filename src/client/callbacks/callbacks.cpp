#include <utils/hook/hook.hpp>

#include <callbacks/callbacks.hpp>

namespace ddr
{
	void callbacks::init()
	{
		callbacks::on(type::main_loop, []() -> void
		{
			const auto $ = std::lock_guard<std::mutex>(callbacks::mtx_);

			for (const auto callback : callbacks::once_callbacks_)
			{
				callback();
			}

			callbacks::once_callbacks_.clear();
		});
	}

	void callbacks::on(callbacks::type type, utils::callback<void __cdecl()> callback)
	{
		callbacks::basic_callbacks_[type].emplace_back(callback);
	}

	void callbacks::on(const std::initializer_list<callbacks::type>& types, utils::callback<void __cdecl()> callback)
	{
		for (const auto type : types)
		{
			callbacks::basic_callbacks_[type].emplace_back(callback);
		}
	}

	void callbacks::once(utils::callback<void __cdecl()> callback)
	{
		const auto $ = std::lock_guard<std::mutex>(callbacks::mtx_);

		callbacks::once_callbacks_.emplace_back(callback);
	}

	void callbacks::run_basic_callbacks(callbacks::type type)
	{
		for (const auto callback : callbacks::basic_callbacks_[type])
		{
			callback();
		}
	}

	std::mutex callbacks::mtx_;
	std::vector<utils::callback<void __cdecl()>> callbacks::once_callbacks_;

	std::unordered_map<callbacks::type, std::vector<utils::callback<void __cdecl()>>> callbacks::basic_callbacks_;
}