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

		//Jump over fps counter
		utils::hook::jump(0x0000000140013E22, 0x0000000140013E31);
	}

	void menus::update()
	{
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
		}

		static bool once = false;
		if (!once)
		{
			ImGui::InsertNotification({ ImGuiToastType_Success, 3000, "Welcome to DDRedux!" });
			once = true;
		}

		//Imgui-notify render
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f); // Round borders
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(43.f / 255.f, 43.f / 255.f, 43.f / 255.f, 100.f / 255.f)); // Background color
		ImGui::RenderNotifications(); // <-- Here we render all notifications
		ImGui::PopStyleVar(1); // Don't forget to Pop()
		ImGui::PopStyleColor(1);
	}
}