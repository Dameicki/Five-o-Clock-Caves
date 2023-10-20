#include "ActionLever.h"

ActionLever::ActionLever()
{
}

ActionLever::ActionLever(bool isActive, bool isUsable)
{
    _isActive = isActive;
    _isUsable = isUsable;
}

std::shared_ptr<Component> ActionLever::GetCopyComponent()
{
    return std::make_shared<ActionLever>(ActionLever(_isActive, _isUsable));
}

void ActionLever::SetUp()
{
    if (_isActive) {
        _targetRotation = -30.0f;
    }
    else {
        _targetRotation = -130.0f;
    }
}

void ActionLever::Update()
{
    float currentRotation = m_gameObject->m_transform->GetRotationEulerDeg().y;
    if (currentRotation != _targetRotation)
    {
        float rotDiff = currentRotation - _targetRotation;
        if (rotDiff > 4) {
            m_gameObject->m_transform->AddAxisRotation(-150 * TIME.GetDeltaTime(), 2);
        }
        else if (rotDiff < -4) {
            m_gameObject->m_transform->AddAxisRotation(150 * TIME.GetDeltaTime(), 2);
        }
        else {
            m_gameObject->m_transform->SetRotation(0, _targetRotation, 0);
        }
    }
}

void ActionLever::ActionStart()
{
    _targetRotation = -30.0f;
}

void ActionLever::ActionStop()
{
    _targetRotation = -130.0f;
}

void ActionLever::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
    ImGui::Text(" ");
    ImGui::Text("=== [ ActionLever ] ===");
    ImGui::Checkbox("IsUsable", &_isUsable);
    ImGui::Checkbox("IsActive", &_isActive);
}
