#include "Level.h"

Level::Level()
{
	type = LEVEL;
}

std::shared_ptr<Component> Level::GetCopyComponent()
{
	std::shared_ptr<Component> copyComponent = std::make_shared<Level>(Level());
	return copyComponent;
}

void Level::SetUp()
{
	_lights = m_gameObject->GetComponentsListInChildren<LightBase>(POINT_LIGHT);
	_lights.splice(_lights.end(), m_gameObject->GetComponentsListInChildren<LightBase>(SPOT_LIGHT)); // Spot ligty nie działają poprawnie
	_lights.splice(_lights.end(),m_gameObject->GetComponentsListInChildren<LightBase>(DIR_LIGHT));
	type = LEVEL;
}

void Level::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	ImGui::Text(" ");

	string tmp = "[ Level " + to_string(index) + " ]";// nawa jest tu
	if (ImGui::CollapsingHeader(tmp.c_str()))
	{
		bool enabledTMP = enabled;	// stan włącznika												
		ImGui::Checkbox("enabled", &enabledTMP);

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.8f, 0.1f, 1.0f }); // zielony
		if (ImGui::Button("Lights On"))
			LightsOn();
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.7f, 0.1f, 0.1f, 1.0f }); // czerwony
		if (ImGui::Button("Lights Off"))
			LightsOff();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		if (ImGui::Button(" Refresh Light List  "))
			SetUp();	   

		for (auto& light : _lights)
		{
			ImGui::Text(light->GetOwner()->m_name.c_str());
		}

		this->SetEnabled(enabledTMP);			// metoda która reaguje na stan włącznika
	}
}

void Level::LightsOn()
{
	for (auto& light : _lights)
	{
		light->SetEnabled(true);
	}
}

void Level::LightsOff()
{
	for (auto& light : _lights)
	{
		light->SetEnabled(false);
	}
}
