#include "Lever.h"

Lever::Lever()
{
	type = LEVER;
}

std::shared_ptr<Component> Lever::GetCopyComponent()
{
	return std::make_shared<Lever>(Lever());
}

void Lever::Update()
{
	if (_waiting)
	{
		if (CheckIfAllActionsAreSet())
		{
			if (!Delay(_turnOffTime , true))
			{
				RunActiveOnActions();
				_waiting = false;
			}
		}
	}
	if (_cube != nullptr) _cube->SetColor(glm::vec3(0.2f));
}

void Lever::Trigger(std::shared_ptr<CollisionResult> collResult)
{
	if (collResult->GetObjectA()->GetCollisionLayer() == PLAYER)
		if (_cube != nullptr) _cube->SetColor(glm::vec3(1.0f));
}

void Lever::Interact(std::shared_ptr<GameObject> player)
{
	if (!_waiting)
	{
		RunActiveOnActions();
		if (_turnOffTime > 0 && CheckIfAllActionsAreSet()) _waiting = true;
	}
}

void Lever::AddAction(std::shared_ptr<ActionBase> action)
{
	_actions.push_back(action);
}

bool Lever::CheckIfAllActionsAreSet()
{
	bool allPlatformsSet = true;
	for (auto& action : _actions)
	{
		if (!action->GetIsUsable())
		{
			allPlatformsSet = false;
			break;
		}
	}
	return allPlatformsSet;
}

void Lever::RemoveAction(int i)
{
	if (i < _actions.size())
	{
		_actions.erase(_actions.begin() + i);
		_tmpId = 0;
	}
}

void Lever::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	ImGui::Text(" ");
	ImGui::Text("=== [ Lever ] ===");
	int tmpLenght = _actions.size();
	if (ImGui::Button("Add"))
		AddAction(dynamic_pointer_cast<ActionBase>(imguiSystem->GetSavedComponent()));
	ImGui::InputInt("Remove ID", (int*)&_tmpId);
	if (ImGui::Button("Remove Action"))
	{
		RemoveAction(_tmpId);
	}
	string tmp;
	int i = 0;
	for (auto& action : _actions)
	{
		tmp = std::to_string(i) + ". " + action->GetOwner()->m_name;
		ImGui::Text(tmp.c_str());
		i++;
	}
	ImGui::Text(" ");
	ImGui::InputFloat("TurnOffTime", &_turnOffTime);

	bool tmpBool;
	if (_puzzleCheck != nullptr)
		tmpBool = true;
	else
		tmpBool = false;

	ImGui::Text(" ");
	ImGui::Checkbox("Has puzzlecheck", &tmpBool);
	if (ImGui::Button("Set PuzzleCheck"))
	{
		_puzzleCheck = dynamic_pointer_cast<PuzzleChecker>(imguiSystem->GetSavedComponent());
	}
	if (ImGui::Button("Remove PuzzleCheck"))
	{
		_puzzleCheck = nullptr;
	}
	ImGui::Text(" ");
	if (ImGui::Button("Activate"))
	{
		Interact(nullptr);
	}
	ImGui::Text(" ");
	if (_cube != nullptr)
		tmpBool = true;
	else
		tmpBool = false;
	ImGui::Checkbox("Has cube", &tmpBool);
	if (ImGui::Button("Set cube"))
	{
		SetCube(dynamic_pointer_cast<MeshRenderer>(imguiSystem->GetSavedComponent()));
	}
}

void Lever::SetCube(std::shared_ptr<MeshRenderer> box)
{
	_cube = box;
}

void Lever::RunActiveOnActions()
{
	if (CheckIfAllActionsAreSet())
	{
		AUDIO.playEffect("res/audio/lever.ogg", 0.1f, 1);
		for (auto& action : _actions)
		{
			action->Active();
		}
	}
	if (_puzzleCheck != nullptr) _puzzleCheck->InspectElements();
}
