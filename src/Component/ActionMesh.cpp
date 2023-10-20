#include "ActionMesh.h"

ActionMesh::ActionMesh()
{
	type = ACTION_MESH;
}

std::shared_ptr<Component> ActionMesh::GetCopyComponent()
{
	std::shared_ptr<Component> copyComponent = std::make_shared<ActionMesh>(ActionMesh());
	return copyComponent;
}

void ActionMesh::SetUp()
{
	//_meshRenderer = dynamic_pointer_cast<MeshRenderer>(m_gameObject->GetComponent<MeshRenderer>(MESH_RENDERER));
	_meshRenderer = m_gameObject->GetComponent<MeshRenderer>(MESH_RENDERER);

	_meshRenderer->GetEnabled();

}

void ActionMesh::ActionStart()
{
	_meshRenderer->SetEnabled(true);
}

void ActionMesh::ActionStop()
{
	_meshRenderer->SetEnabled(false);
}

void ActionMesh::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	ImGui::Text(" ");

	string tmp = "[ Action Mesh " + to_string(index) + " ]";// nawa jest tu
	if (ImGui::CollapsingHeader(tmp.c_str()))
	{
		bool enabledTMP = enabled;	// stan włącznika
		ImGui::Checkbox("enabled", &enabledTMP);

		ImGui::Checkbox("IsUsable", &_isUsable);
		ImGui::Checkbox("IsActive", &_isActive);

		this->SetEnabled(enabledTMP);			// metoda która reaguje na stan włącznika
	}
}
