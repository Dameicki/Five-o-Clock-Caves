#include "PlaceForCog.h"

PlaceForCog::PlaceForCog()
{
	type = PLACE_FOR_COG;
}


void PlaceForCog::Update()
{
	if (_cube != nullptr) _cube->SetColor(glm::vec3(0.2f));
}

void PlaceForCog::Trigger(std::shared_ptr<CollisionResult> collResult)
{
	if (collResult->GetObjectA()->GetCollisionLayer() == COG)
	{
		cout << "A: Zebatka w poblizu" << endl;
		collResult->GetObjectA()->GetOwner()->SetEnabled(false);
		RunActiveOnActions();
	}
	if (collResult->GetObjectB()->GetCollisionLayer() == COG)
	{
		cout << "B: Zebatka w poblizu" << endl;
	}

	if (collResult->GetObjectA()->GetCollisionLayer() == PLAYER)
	{
		shared_ptr<PlayerInteraction> playerInteraction = collResult->GetObjectA()->GetOwner()->GetComponent<PlayerInteraction>(PLAYER_INTERACTION);
		if (playerInteraction->GetInteractableObject() != nullptr)
		{
			if (playerInteraction->GetInteractableObject()->GetType() == COG_COMP)
			{
				if (_cube != nullptr)
				{
					_cube->SetColor(glm::vec3(1.0f));
				}
			}
		}
	}
}


void PlaceForCog::Interact(std::shared_ptr<GameObject> player)
{

}

void PlaceForCog::AddAction(std::shared_ptr<ActionBase> action)
{
	_actions.push_back(action);
}

void PlaceForCog::RemoveAction(int i)
{
	if (i < _actions.size())
	{
		_actions.erase(_actions.begin() + i);
		_tmpId = 0;
	}
}

std::shared_ptr<Component> PlaceForCog::GetCopyComponent()
{
	std::shared_ptr<Component> copyComponent = std::make_shared<PlaceForCog>();
	//copyComponent->enabled = this->enabled;
	return copyComponent;
}

void PlaceForCog::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	ImGui::Text(" ");

	string tmp = "[ PlaceForCog " + to_string(index) + " ]";// nawa jest tu
	if (ImGui::CollapsingHeader(tmp.c_str()))
	{
		bool enabledTMP = enabled;	// stan włącznika												
		ImGui::Checkbox("enabled", &enabledTMP);

		int tmpLenght = _actions.size();
		if (ImGui::Button("Add"))
			AddAction(dynamic_pointer_cast<ActionBase>(imguiSystem->GetSavedComponent()));
		ImGui::InputInt("Remove ID", (int*)&_tmpId);
		if (ImGui::Button("Remove Action"))
		{
			RemoveAction(_tmpId);
		}
		string tmp;
		for (auto& action : _actions)
		{
			tmp = action->GetOwner()->m_name;
			ImGui::Text(tmp.c_str());
		}
		ImGui::Text(" ");

		bool tmpBool;
		if (_puzzleCheck != nullptr)
			tmpBool = true;
		else
			tmpBool = false;

		ImGui::Text(" ");
		ImGui::Checkbox("Has puzzlecheck", &tmpBool);
		if (ImGui::Button("Add PuzzleCheck"))
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
			RunActiveOnActions();
		}

		if (ImGui::Button("Set cube"))
		{
			_cube = dynamic_pointer_cast<MeshRenderer>(imguiSystem->GetSavedComponent());
		}

		this->SetEnabled(enabledTMP);			// metoda która reaguje na stan włącznika
	}
}

void PlaceForCog::RunActiveOnActions()
{
	for (auto& action : _actions)
	{
		action->Active();
	}

	if (_cube != nullptr) 
		_cube->SetColor(glm::vec3(0.2f));
	_cube = nullptr;

	if (_puzzleCheck != nullptr) _puzzleCheck->InspectElements();
}
