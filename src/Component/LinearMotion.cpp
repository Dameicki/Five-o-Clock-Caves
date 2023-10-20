#include "LinearMotion.h"

LinearMotion::LinearMotion(glm::vec3 movementVector, float timeToFinish, bool finish)
{
    type = LINEAR_MOTION;
    _movementVector = movementVector;
    _tmpMovementVector = glm::vec3(0.0f);
    _timeToFinish = timeToFinish;
    _finish = finish;
}

void LinearMotion::Update()
{
    _timer += TIME.GetDeltaTime();
    if (!_finish || (_finish && _timer - _timeToFinish < 0))
    {
        _tmpMovementVector = _movementVector * (1 / _timeToFinish) * TIME.GetDeltaTime();
        m_gameObject->m_transform->AddPosition(_movementVector * (1/_timeToFinish) * TIME.GetDeltaTime());
    }
    _tmpMovementVector = glm::vec3(0.0f);
}

void LinearMotion::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
    ImGui::Text(" ");

    bool enabledTMP = enabled;	// stan włącznika
    ImGui::Checkbox("=== [ Linear Motion ] ===", &enabledTMP); // nazwa jest tu

    ImGui::InputFloat3("Movement Vector", (float*)&_movementVector, "%.3f");
    ImGui::InputFloat("Time To Finish", (float*)&_timeToFinish);
    ImGui::Checkbox("Stop At End", &_finish);

    this->SetEnabled(enabledTMP);			// metoda która reaguje na stan włącznika
}