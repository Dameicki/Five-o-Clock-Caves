#include "ActionDoor.h"

ActionDoor::ActionDoor()
{
	type = ACTION_DOOR;
}

ActionDoor::ActionDoor(bool locked): _locked(locked)
{
	type = ACTION_DOOR;
}

std::shared_ptr<Component> ActionDoor::GetCopyComponent()
{
	std::shared_ptr<Component> copyComponent = std::make_shared<ActionDoor>(ActionDoor(_locked));
	return copyComponent;
}

bool ActionDoor::GetLocked()
{
	return _locked;
}

void ActionDoor::ActionStart()
{
	_locked = false;
}

void ActionDoor::ActionStop()
{
	_locked = true;
}

void ActionDoor::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	ImGui::Text(" ");

	string tmp = "[ Action Door " + to_string(index) + " ]";// nawa jest tu
	if (ImGui::CollapsingHeader(tmp.c_str()))
	{
		bool enabledTMP = enabled;	// stan włącznika
		ImGui::Checkbox("enabled", &enabledTMP);

		ImGui::Checkbox("locked", &_locked);

		ImGui::Checkbox("IsUsable", &_isUsable);
		ImGui::Checkbox("IsActive", &_isActive);

		this->SetEnabled(enabledTMP);			// metoda która reaguje na stan włącznika
	}
}
