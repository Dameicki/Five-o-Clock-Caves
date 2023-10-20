#include "ActionBox.h"

ActionBox::ActionBox()
{
}

std::shared_ptr<Component> ActionBox::GetCopyComponent()
{
    std::shared_ptr<Component> copyComponent = std::make_shared<ActionBox>(ActionBox());
    return copyComponent;
}

void ActionBox::ActionStart()
{
    ResetPosition();
}

void ActionBox::ActionStop()
{
    ResetPosition();
}

void ActionBox::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
    ImGui::Text(" ");
    ImGui::Text("=== [ ActionBox ] ===");
    ImGui::Checkbox("IsUsable", &_isUsable);
    ImGui::Checkbox("IsActive", &_isActive);
    ImGui::InputFloat3("StartVector", (float*)&_startPosition, "%.3f");

    if (ImGui::Button("Set StartPosition"))
    {
        _startPosition = m_gameObject->m_transform->GetPosition();
    }
}

void ActionBox::ResetPosition()
{
    m_gameObject->m_transform->SetPosition(_startPosition);
    m_gameObject->GetComponent<BoxController>(BOX_CONTROLLER)->SetUpwardSpeed(0);
}
