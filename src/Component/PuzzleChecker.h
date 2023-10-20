#pragma once

#include "Component.h"
#include "ActionBase.h"
#include <cereal/types/vector.hpp>

class PuzzleChecker : public Component {
public:
	PuzzleChecker();

	void SetUp();

	void InspectElements();

	void AddAction(std::shared_ptr<ActionBase> action);
	void RemoveAction(int i);

	void AddDesiredState();
	void RemoveDesiredState(int i);

	void AddTarget(std::shared_ptr<ActionBase> target);
	void RemoveTarget(int i);

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	
	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			CEREAL_NVP(_actions),
			CEREAL_NVP(_desiredActionStates),
			CEREAL_NVP(_completionTargets),
			CEREAL_NVP(_oneTimeCompletion)
		);
	}
	

private:
	std::vector<std::shared_ptr<ActionBase>> _actions;
	std::vector<bool> _desiredActionStates;
	std::vector<std::shared_ptr<ActionBase>> _completionTargets;
	std::vector<bool> _startingStates;

	bool _oneTimeCompletion = false;
	bool _puzzleLockCompletion = false;
	int _tmpId = 0;
	bool _tmpState = false;
};

CEREAL_REGISTER_TYPE(PuzzleChecker);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, PuzzleChecker);