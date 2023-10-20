#pragma once

#include "Component.h"
#include "ActionBase.h"
#include "Interactable.h"
#include "PlayerInteraction.h"
#include "PuzzleChecker.h"
#include <cereal/types/vector.hpp>

class PlaceForCog : public Interactable {
public:
	PlaceForCog();

	void Update() override;
	void Trigger(std::shared_ptr<CollisionResult> collResult) override;
	void Interact(std::shared_ptr<GameObject> player) override;

	void AddAction(std::shared_ptr<ActionBase> action);
	void RemoveAction(int i);

	std::shared_ptr<Component> GetCopyComponent() override;

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			cereal::base_class<Interactable>(this),
			CEREAL_NVP(_actions),
			CEREAL_NVP(_puzzleCheck),
			CEREAL_NVP(_cube)
			);
	}


private:
	std::vector<std::shared_ptr<ActionBase>> _actions;
	
	std::shared_ptr<PuzzleChecker> _puzzleCheck = nullptr;

	bool _load = true;

	std::shared_ptr<MeshRenderer> _cube = nullptr;

	void RunActiveOnActions();
	int _tmpId = 0;
};

CEREAL_REGISTER_TYPE(PlaceForCog);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Interactable, PlaceForCog);