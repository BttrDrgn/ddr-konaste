#include <game/menus/menus.hpp>
#include <game/core/core.hpp>

#include <utils/format/format.hpp>

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
				ImGui::SetNextWindowPos(ImVec2{ 0, 695 });
				ImGui::SetNextWindowSize(ImVec2{ 1280, 15 });
				ImGui::Begin("Diagnostics", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);

				ImGui::Text("FPS: %4.1f | FT: %5.2f ms", core::frame_rate, (1000.0f / core::frame_rate));

				ImGui::End();
			}
		}
	}
}