#include "BoxController.h"

BoxController::BoxController()
{
    type = BOX_CONTROLLER;
}

BoxController::BoxController(float gravity, float weight): _gravity(gravity), _weight(weight)
{
    type = BOX_CONTROLLER;
}

std::shared_ptr<Component> BoxController::GetCopyComponent()
{
    std::shared_ptr<Component> copyComponent = std::make_shared<BoxController>(BoxController(_gravity,_weight));
    return copyComponent;
}

void BoxController::Update()
{
    BoxMove();
}


void BoxController::Collision(std::shared_ptr<CollisionResult> collResult)
{
    float tmpForce = _weight;
    if (collResult->GetObjectB()->GetCollisionLayer() == PLAYER)
    {
        tmpForce -= collResult->GetObjectB()->GetOwner()->GetComponent<PlayerController>(PLAYER_CONTROLLER)->GetPushForce();
        if (tmpForce < 1) tmpForce = 1;
        m_gameObject->m_transform->AddPosition(collResult->GetSeparationVector() / tmpForce);
    }
    else {
        m_gameObject->m_transform->AddPosition(collResult->GetSeparationVector());
    }
    

    if (collResult->GetDirectionVector() == glm::vec3(0.0f, -1.0f, 0.0f) && _upwardSpeed < 0)
    {
        _upwardSpeed = 0;
    }
}

void BoxController::SetUpwardSpeed(float speed)
{
    _upwardSpeed = speed;
}

void BoxController::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
    ImGui::Text(" ");		// Odstęp

    string tmp = "[ BoxController " + to_string(index) + " ]";// nawa jest tu
    if (ImGui::CollapsingHeader(tmp.c_str()))
    {
        static int tmpKey = 0;

        bool enabledTMP = enabled;	// stan włącznika
        ImGui::Checkbox("enabled", &enabledTMP);

        ImGui::InputFloat("Gravity", (float*)&_gravity);
        ImGui::InputFloat("Weight", (float*)&_weight);

        this->SetEnabled(enabledTMP);			// metoda która reaguje na stan włącznika
    }
}

void BoxController::BoxMove()
{
    _upwardSpeed += _gravity * TIME.GetDeltaTime();
    m_gameObject->m_transform->AddPosition(glm::vec3(0.0f, _upwardSpeed * TIME.GetDeltaTime(), 0.0f));
}