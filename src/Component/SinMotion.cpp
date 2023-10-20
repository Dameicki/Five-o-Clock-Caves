#include "SinMotion.h"

SinMotion::SinMotion(glm::vec3 movementVector, float timeToFinish)
{
    type = SIN_MOTION;
    _movementVector = movementVector;
    _tmpMovementVector = glm::vec3(0.0f);
    _timeToFinish = timeToFinish;
}

void SinMotion::Update()
{
    _timer += TIME.GetDeltaTime();
    _tmpMovementVector = (_movementVector / _timeToFinish * TIME.GetDeltaTime() * 0.5f) * glm::sin(_timer / _timeToFinish);
    m_gameObject->m_transform->AddPosition(_tmpMovementVector);
}

void SinMotion::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
    string tmp = "[ SinMotion " + to_string(index) + " ]";
    if (ImGui::CollapsingHeader(tmp.c_str()))
    {

        bool enabledTMP = enabled;	// stan włącznika
        ImGui::Checkbox("=== [ Sin Motion ] ===", &enabledTMP); // nazwa jest tu

        ImGui::InputFloat3("Movement Vector", (float*)&_movementVector, "%.3f");
        ImGui::InputFloat("Time To Finish", (float*)&_timeToFinish);

        this->SetEnabled(enabledTMP);			// metoda która reaguje na stan włącznika
    }
}