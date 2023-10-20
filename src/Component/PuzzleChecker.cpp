#include "PuzzleChecker.h"

PuzzleChecker::PuzzleChecker()
{
	type = PUZZLE_CHECKER;
}

void PuzzleChecker::SetUp()
{
	_startingStates.clear();
	for (auto& action : _completionTargets)
	{
		_startingStates.push_back(action->GetIsActive());
	}
}

void PuzzleChecker::InspectElements()
{
	bool puzzleComplete = true;
	if (!_puzzleLockCompletion)
	{
		for (int i = 0; i < _actions.size(); i++)
		{
			if (_actions[i]->GetIsActive() != _desiredActionStates[i])
			{
				puzzleComplete = false;
			}
		}
	}
	else { return; }
	if (puzzleComplete)
	{
		if (_oneTimeCompletion) _puzzleLockCompletion = true;
		for (auto& action : _completionTargets)
		{
			action->Active();
		}
	} else {
		for (int i = 0; i < _completionTargets.size(); i++)
		{
			if (_completionTargets[i]->GetIsActive() != _startingStates[i])
			{
				_completionTargets[i]->Active();
			}
		}
	}
}

void PuzzleChecker::AddAction(std::shared_ptr<ActionBase> action)
{
	_actions.push_back(action);
}

void PuzzleChecker::RemoveAction(int i)
{
	if (i < _actions.size())
	{
		_actions.erase(_actions.begin() + i);
		_tmpId = 0;
	}
}

void PuzzleChecker::AddDesiredState()
{
	_desiredActionStates.push_back(_tmpState);
}

void PuzzleChecker::RemoveDesiredState(int i)
{
	if (i < _desiredActionStates.size())
	{
		_desiredActionStates.erase(_desiredActionStates.begin() + i);
		_tmpId = 0;
	}
}

void PuzzleChecker::AddTarget(std::shared_ptr<ActionBase> target)
{
	_completionTargets.push_back(target);
}

void PuzzleChecker::RemoveTarget(int i)
{
	if (i < _completionTargets.size())
	{
		_completionTargets.erase(_completionTargets.begin() + i);
		_tmpId = 0;
	}
}

void PuzzleChecker::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	ImGui::Text(" ");
	ImGui::Text("=== [ Puzzle Checker ] ===");
	int tmpLenght = _actions.size();
	ImGui::Checkbox("One Time Completion", &_oneTimeCompletion);
	ImGui::Text(" ");
	//Actions
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
	i = 0;

	//Desired states
	ImGui::Text(" ");
	ImGui::Checkbox("State", &_tmpState);
	if (ImGui::Button("Add State"))
		AddDesiredState();
	ImGui::InputInt("Remove ID", (int*)&_tmpId);
	if (ImGui::Button("Remove State"))
	{
		RemoveDesiredState(_tmpId);
	}
	for (bool state : _desiredActionStates)
	{
		if (state) tmp = std::to_string(i) + ". " + "True";
		else tmp = std::to_string(i) + ". " + "False";
		ImGui::Text(tmp.c_str());
		i++;
	}
	i = 0;
	//Target actions
	ImGui::Text(" ");
	if (ImGui::Button("Add Target"))
	{
		AddTarget(dynamic_pointer_cast<ActionBase>(imguiSystem->GetSavedComponent()));
		SetUp();
	}
	ImGui::InputInt("Remove ID", (int*)&_tmpId);
	if (ImGui::Button("Remove Target"))
	{
		RemoveTarget(_tmpId);
		SetUp();
	}
	for (auto& action : _completionTargets)
	{
		tmp = std::to_string(i) + ". " + action->GetOwner()->m_name;
		ImGui::Text(tmp.c_str());
		i++;
	}
}
