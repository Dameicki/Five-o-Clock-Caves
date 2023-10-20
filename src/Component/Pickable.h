#pragma once
#include "Interactable.h"

class Pickable : public Interactable
{
public :
	Pickable();

	void Interact(std::shared_ptr<GameObject> player) override;

	virtual std::shared_ptr<Component> GetCopyComponent() override;

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override; 

	void Trigger(std::shared_ptr<CollisionResult> collResult) override;

	void SetUp() override;
protected:
	bool _held = false;
	void Throw();
	void PickUp(std::shared_ptr<GameObject> player);
	std::shared_ptr<GameObject> oldParent;

};

CEREAL_REGISTER_TYPE(Pickable);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Interactable, Pickable);