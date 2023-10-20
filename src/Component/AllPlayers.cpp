#include "AllPlayers.h"

AllPlayers::AllPlayers()
{
	type = ALL_PLAYERS;
}

std::shared_ptr<Component> AllPlayers::GetCopyComponent()
{
	std::shared_ptr<Component> copyComponent = std::make_shared<AllPlayers>(AllPlayers());
	return copyComponent;
}

void AllPlayers::SetUp()
{
	_players = m_gameObject->GetComponentsListInChildren<PlayerController>(PLAYER_CONTROLLER);
}

void AllPlayers::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	ImGui::Text(" ");

	string tmp = "[ All Players " + to_string(index) + " ]";// nawa jest tu
	if (ImGui::CollapsingHeader(tmp.c_str()))
	{
		bool enabledTMP = enabled;	// stan włącznika												
		ImGui::Checkbox("enabled", &enabledTMP);

		//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.8f, 0.1f, 1.0f }); // zielony
		//if (ImGui::Button("Lights On"))
		//	LightsOn();
		//ImGui::SameLine();
		//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.7f, 0.1f, 0.1f, 1.0f }); // czerwony
		//if (ImGui::Button("Lights Off"))
		//	LightsOff();
		//ImGui::PopStyleColor();
		//ImGui::PopStyleColor();
		//if (ImGui::Button(" Refresh Light List  "))
		//	SetUp();	   

		for (auto& player : _players)
		{
			ImGui::Text(player->GetOwner()->m_name.c_str());
		}

		this->SetEnabled(enabledTMP);			// metoda która reaguje na stan włącznika
	}
}

void AllPlayers::RemovePowers()
{
	for (auto& player : _players)
	{
		// Usuwanie super mocy
		player->SetJumps(1);
		player->SetPushForce(0);
	}
}
