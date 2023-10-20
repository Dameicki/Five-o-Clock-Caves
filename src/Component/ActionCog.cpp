#include "ActionCog.h"

ActionCog::ActionCog()
{
}

ActionCog::ActionCog(int axis, float rotationSpeed, bool isActive, bool isUsable): _axis(axis), _rotationSpeed(rotationSpeed)
{
    _isActive = isActive;
    _isUsable = isUsable;
}

std::shared_ptr<Component> ActionCog::GetCopyComponent()
{
    std::shared_ptr<Component> copyComponent = std::make_shared<ActionCog>(ActionCog(_axis, _rotationSpeed,_isActive,_isUsable));
    return copyComponent;
}

void ActionCog::Run()
{
    m_gameObject->m_transform->AddAxisRotation(_rotationSpeed * TIME.GetDeltaTime(), _axis);
}

void ActionCog::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
    string tmp = "[ ActionCog " + to_string(index) + " ]";
    if (ImGui::CollapsingHeader(tmp.c_str()))
    {
        ImGui::Checkbox("IsUsable", &_isUsable);
        ImGui::Checkbox("IsActive", &_isActive);
        ImGui::InputInt("Axis", &_axis);
        ImGui::InputFloat("RotationSpeed", &_rotationSpeed);
    }
}
