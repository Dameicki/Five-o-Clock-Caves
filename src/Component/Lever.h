#pragma once

#include "Component.h"
#include "ActionBase.h"
#include "Interactable.h"
#include "PlayerInteraction.h"
#include "PuzzleChecker.h"
#include <cereal/types/vector.hpp>

class Lever : public Interactable {
public:
	Lever();

	std::shared_ptr<Component> GetCopyComponent() override;

	void Update() override;
	void Trigger(std::shared_ptr<CollisionResult> collResult) override;

	void Interact(std::shared_ptr<GameObject> player) override;

	void AddAction(std::shared_ptr<ActionBase> action);

	bool CheckIfAllActionsAreSet();
	void RemoveAction(int i);

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	void SetCube(std::shared_ptr<MeshRenderer> box);

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			cereal::base_class<Interactable>(this),
			CEREAL_NVP(_actions),
			CEREAL_NVP(_turnOffTime),
			CEREAL_NVP(_puzzleCheck),
			CEREAL_NVP(_cube)
		);
	}


private:
	std::vector<std::shared_ptr<ActionBase>> _actions;
	float _turnOffTime = 0.0f;
	std::shared_ptr<PuzzleChecker> _puzzleCheck = nullptr;
	std::shared_ptr<MeshRenderer> _cube = nullptr;

	void RunActiveOnActions();
	int _tmpId = 0;
	bool _waiting = false;
};

CEREAL_REGISTER_TYPE(Lever);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Interactable, Lever);