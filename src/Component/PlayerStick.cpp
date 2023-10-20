#include "PlayerStick.h"

PlayerStick::PlayerStick(std::shared_ptr<Component> platformPtr, bool type) :
    _platformPtr(platformPtr), _type(type)
{
}

std::shared_ptr<Component> PlayerStick::GetCopyComponent()
{
    return std::make_shared<PlayerStick>(PlayerStick(nullptr, true));
}

void PlayerStick::Trigger(std::shared_ptr<CollisionResult> collResult)
{
    if (_platformPtr != nullptr)
    {
        if (_type)
            collResult->GetObjectA()->GetOwner()->m_transform->AddPosition(dynamic_pointer_cast<Platform>(_platformPtr)->GetTmpMovementVector());
        else
            collResult->GetObjectA()->GetOwner()->m_transform->AddPosition(dynamic_cast<MotionBase&>(*_platformPtr).GetTmpMovementVector());
    }
}

void PlayerStick::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
    ImGui::Text(" ");

    bool enabledTMP = enabled;	// stan włącznika
    ImGui::Checkbox("=== [ Player Stick ] ===", &enabledTMP); // nazwa jest tu

    bool tmpBool;
    if (_platformPtr != nullptr)
        tmpBool = true;
    else
        tmpBool = false;

    if (ImGui::Button("Add"))
        AddPlatformPtr(dynamic_pointer_cast<Platform>(imguiSystem->GetSavedComponent()));

    ImGui::Checkbox("Has Platform", &tmpBool);

    this->SetEnabled(enabledTMP);			// metoda która reaguje na stan włącznika
}

void PlayerStick::AddPlatformPtr(std::shared_ptr<Platform> ptr)
{
    _platformPtr = ptr;
}
