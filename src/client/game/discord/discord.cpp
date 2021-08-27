#include <utils/console/console.hpp>
#include <utils/hook/hook.hpp>
#include <utils/format/format.hpp>

#include <game/game.hpp>

#include <game/discord/discord.hpp>

#include <discord.h>


namespace ddr
{
	discord::Core* core{};
	discord::Activity activity{};
	bool enabled;

	void drpc::init()
	{
		if (const auto result = discord::Core::Create(880353071123816449, ::DiscordCreateFlags_NoRequireDiscord, &core); result == discord::Result::Ok)
		{
			if (result == discord::Result::Ok) enabled = true;
			else enabled = false;

			core->SetLogHook(discord::LogLevel::Info, [](auto, auto message)
			{
				PRINT_INFO("%s", message);
			});

			core->SetLogHook(discord::LogLevel::Warn, [](auto, auto message)
			{
				PRINT_WARNING("%s", message);
			});

			core->SetLogHook(discord::LogLevel::Error, [](auto, auto message)
			{
				PRINT_ERROR("%s", message);
			});

			drpc::change_large_image("logo", "DDR");
			activity.GetTimestamps().SetStart(std::time(nullptr));

			drpc::update();

			if (result == discord::Result::Ok)
			{
				std::thread([]() -> void
				{
					for (;;)
					{
						core->RunCallbacks();
						std::this_thread::sleep_for(50ms);
					}
				}).detach();
			}
		}
	}

	void drpc::change_status(const std::string& text)
	{
		if (enabled)
		{
			activity.SetState(text.c_str());

			drpc::update();
		}
	}

	void drpc::change_large_image(const char* image, const char* text)
	{
		if (enabled)
		{
			activity.GetAssets().SetLargeImage(image);
			activity.GetAssets().SetLargeText(text);

			drpc::update();
		}
	}

	void drpc::change_small_image(const std::string& image, const std::string& text)
	{
		if (enabled)
		{
			activity.GetAssets().SetSmallImage(image.c_str());
			activity.GetAssets().SetSmallText(text.c_str());

			drpc::update();
		}
	}

	void drpc::update()
	{
		if (enabled)
		{
			core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});
		}
	}
}
