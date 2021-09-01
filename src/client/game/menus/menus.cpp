#include <game/menus/menus.hpp>
#include <game/core/core.hpp>

#include <utils/format/format.hpp>

#include <callbacks/callbacks.hpp>

#include <imgui_notify.h>

namespace ddr::game
{
	bool menus::active;

	//States
	bool menus::states::diag;
	bool menus::states::shortcuts;
	bool menus::states::settings;

	void menus::init()
	{
		menus::active = true;
		ImGuiIO& io = ImGui::GetIO();

		//Imgui-notify init
		ImFontConfig font_cfg;
		font_cfg.FontDataOwnedByAtlas = false;
		io.Fonts->AddFontFromMemoryTTF((void*)tahoma, sizeof(tahoma), 17.f, &font_cfg);
		ImGui::MergeIconsWithLatestFont(16.f, false);

		//States
		menus::states::diag = false;
		menus::states::shortcuts = false;
		menus::states::settings = false;

		//Jump over fps counter
		utils::hook::jump(0x0000000140013E22, 0x0000000140013E31);
	}

	void menus::update()
	{
		static bool info_toast = false;
		if (menus::active)
		{
			ImGuiIO& io = ImGui::GetIO();
			ImGuiStyle& s = ImGui::GetStyle();

			s.WindowBorderSize = { 0.f };

			if (menus::states::diag)
			{
				ImGui::SetNextWindowPos(ImVec2{ 0, 690 });
				ImGui::SetNextWindowSize(ImVec2{ 1280, 20 });
				ImGui::Begin("Diagnostics", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);

				ImGui::Text("FPS: %4.1f | FT: %5.2f ms", core::frame_rate, (1000.0f / core::frame_rate));

				ImGui::End();
			}

			if (menus::states::shortcuts)
			{
				ImGui::SetNextWindowPos(ImVec2(1160, 720 * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
				ImGui::SetNextWindowSize(ImVec2{ 240, 600 });
				ImGui::Begin("Shortcuts", &menus::states::shortcuts, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

				ImGui::Text("[Tab] - Settings");
				ImGui::Text("[F1] - Shortcuts");
				ImGui::Text("[F3] - Toggle ALL menus");
				ImGui::Text("[F12] - Toggle Diagnostic view");

				ImGui::End();
			}

			if (menus::states::settings)
			{
				ImGui::SetNextWindowPos(ImVec2(1280 * 0.5f, 720 * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
				ImGui::SetNextWindowSize(ImVec2{ 800, 600 });
				ImGui::Begin("Settings", &menus::states::settings, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

				ImGui::Checkbox("Show Judgement", &core::judegment);
				ImGui::SameLine();

				static bool save = true;
				ImGui::Checkbox("Save Options", &save);
				ImGui::SameLine();

				static char name[9];
				ImGui::PushItemWidth(115);
				ImGui::InputText("Dancer Name", name, sizeof(name), ImGuiInputTextFlags_CharsUppercase);
				ImGui::PopItemWidth();

				ImGui::NewLine();
				ImGui::NewLine();
				ImGui::NewLine();
				ImGui::NewLine();
				ImGui::NewLine();

				if (ImGui::Button("Save Settings", ImVec2{ 100,25 }))
				{
					callbacks::run_basic_callbacks(callbacks::type::settings_saved);
				}

				ImGui::SameLine();

				if (ImGui::Button("Reset Settings", ImVec2{ 100,25 }))
				{
					callbacks::run_basic_callbacks(callbacks::type::settings_reset);
				}

				ImGui::End();
			}

			if (info_toast)
			{
				info_toast = false;
			}
		}
		else if (!menus::active)
		{
			if (!info_toast)
			{
				ImGui::InsertNotification({ ImGuiToastType_Info, 3000, "Menus disabled!\nPress F3 to toggle the menus.\nPress F1 for shortcuts." });
				info_toast = true;
			}
		}

		//Imgui-notify render
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f); // Round borders
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(43.f / 255.f, 43.f / 255.f, 43.f / 255.f, 100.f / 255.f)); // Background color
		ImGui::RenderNotifications(); // <-- Here we render all notifications
		ImGui::PopStyleVar(1); // Don't forget to Pop()
		ImGui::PopStyleColor(1);
	}
}