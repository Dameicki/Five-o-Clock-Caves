#pragma once

#include <glm/vec3.hpp>

#include "core/GameObject.h"
#include "Component.h"
#include "PlayerController.h"

class GameObject; 
class Component;

class AllPlayers : public Component {
public:
	AllPlayers();

	std::shared_ptr<Component> GetCopyComponent() override;

	void SetUp()override;

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	void RemovePowers();

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this)
		);
	}


private:
	list<shared_ptr<PlayerController>> _players;
	
};
CEREAL_REGISTER_TYPE(AllPlayers);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, AllPlayers);