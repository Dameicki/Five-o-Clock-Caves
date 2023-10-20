#pragma once

#include "core/InputManager.h"
#include "core/GameObject.h"
#include "Component.h"
#include "Interactable.h"

class GameObject;
class Component;
class Interactable;

class PlayerInteraction : public Component
{
public:
	PlayerInteraction(int keyCodeInteract, int keyCodeInteractAlt);

	void Input() override;
	void Update() override;
	void Trigger(std::shared_ptr<CollisionResult> collResult) override;

	void SetUp() override;

	int GetKeyCodeInteract();
	std::shared_ptr<Interactable> GetInteractableObject();

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			CEREAL_NVP(_keyCodeInteract),
			CEREAL_NVP(_keyCodeInteractAlt),
			CEREAL_NVP(_interactableObject)
		);

	}
	bool isHolding = false;

private:
	friend class cereal::access;
	
	PlayerInteraction() {}

	int _keyCodeInteract;
	int _keyCodeInteractAlt;


	std::shared_ptr<Interactable> _interactableObject;
	//objekt do interakcji jeszcze
};


CEREAL_REGISTER_TYPE(PlayerInteraction);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, PlayerInteraction);