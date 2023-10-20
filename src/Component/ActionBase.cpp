#include "ActionBase.h"

ActionBase::ActionBase()
{
    type = ACTION_BASE;
}

void ActionBase::SetIsActive(bool state)
{
	_isActive = state;
}

bool ActionBase::GetIsActive()
{
	return _isActive;
}

void ActionBase::SetIsUsable(bool state)
{
	_isUsable = state;
}

bool ActionBase::GetIsUsable()
{
	return _isUsable;
}

void ActionBase::Start()
{
	if (_isActive == true)	ActionStart();
}

void ActionBase::Update()
{
    if (_isActive == true)	Run();
    else Return();
}

void ActionBase::Active()
{
    if (_isActive == true)
    {
        _isActive = false;
        ActionStop();
    }
    else
    {
        _isActive = true;
        ActionStart();
    }
}

void ActionBase::SetInactive()
{
    if (_isActive)
    {
        _isActive = false;
        ActionStop();
    }
}

void ActionBase::ActionStart()
{
}

void ActionBase::Run()
{
}

void ActionBase::Return()
{
}

void ActionBase::ActionStop()
{
}

void ActionBase::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
    ImGui::Text(" ");
    ImGui::Text("=== [ ActionBase ] ===");
    ImGui::Checkbox("IsUsable", &_isUsable);
    ImGui::Checkbox("IsActive", &_isActive);
}
