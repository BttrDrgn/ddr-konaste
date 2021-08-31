#include <game/menus/menus.hpp>
#include <game/core/core.hpp>

#include <utils/format/format.hpp>

#include <imgui_notify.h>

namespace ddr::game
{
	bool menus::active;
	ImGuiIO& menus::io = ImGuiIO();
	ImGuiStyle& menus::s = ImGuiStyle();

	//States
	bool menus::states::diag;
	bool menus::states::shortcuts;

	void menus::init()
	{
		menus::active = true;
		menus::io = ImGui::GetIO();
		menus::s = ImGui::GetStyle();

		//Imgui-notify init
		ImFontConfig font_cfg;
		font_cfg.FontDataOwnedByAtlas = false;
		menus::io.Fonts->AddFontFromMemoryTTF((void*)tahoma, sizeof(tahoma), 17.f, &font_cfg);
		ImGui::MergeIconsWithLatestFont(16.f, false);

		//States
		menus::states::diag = false;
		menus::states::shortcuts = false;

		//Jump over fps counter
		utils::hook::jump(0x0000000140013E22, 0x0000000140013E31);
	}

	void menus::update()
	{
		static bool info_toast = false;
		if (menus::active)
		{
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
				ImGui::SetNextWindowPos(ImVec2(1280 * 0.5f, 720 * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
				ImGui::SetNextWindowSize(ImVec2{ 800, 600 });
				ImGui::Begin("Shortcuts", nullptr, ImGuiWindowFlags_NoDecoration);

				ImGui::Text("Shortcuts");
				ImGui::NewLine();
				ImGui::NewLine();
				ImGui::Text("[F1] - Shortcuts Menu");
				ImGui::Text("[F3] - Toggle ALL menus");
				ImGui::Text("[F12] - Toggle Diagnostic view");

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