#pragma once

#include <glm/vec3.hpp>

#include "core/GameObject.h"
#include "Component.h"

class GameObject; 
class Component;

class Interactable : public Component {
public:
	Interactable();

	virtual void Interact(std::shared_ptr<GameObject> player);

	virtual void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	bool isPickable = false;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this)
		);
	}

protected:
};

CEREAL_REGISTER_TYPE(Interactable);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Interactable);