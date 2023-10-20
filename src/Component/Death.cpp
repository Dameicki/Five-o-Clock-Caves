#include "Death.h"

Death::Death()
{
}

void Death::Trigger(std::shared_ptr<CollisionResult> collResult)
{
	if(collResult->GetObjectA()->GetCollisionLayer() == PLAYER)
	{
		collResult->GetObjectA()->GetOwner()->GetComponent<PlayerController>(PLAYER_CONTROLLER)->SetUpwardSpeed(0);
		collResult->GetObjectA()->GetOwner()->m_transform->SetPosition(_spawnPoint+glm::vec3(side,0,0));
		side *= -1;
	}
}

void Death::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	ImGui::Text(" ");
	if (ImGui::CollapsingHeader("[ Death ]"))
	{
		ImGui::InputFloat3("Spawn point", (float*)&_spawnPoint, "%.3f");
	}
}

