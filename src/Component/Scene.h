#pragma once

#include <glm/vec3.hpp>

#include "core/GameObject.h"
#include "Core/EntityManager.h"
#include "Component.h"

class GameObject; 
class Component;
class AllPlayers;

class Scene : public Component {
public:
	Scene();

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	void SetCurrentRoom(std::shared_ptr<GameObject> room);

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			CEREAL_NVP(_scenePath),
			CEREAL_NVP(_currentRoom),
			CEREAL_NVP(_dwarfs)
		);
	}
	
	string _scenePath;
	std::shared_ptr<GameObject> _currentRoom;
	std::shared_ptr<GameObject> _dwarfs;
};
CEREAL_REGISTER_TYPE(Scene);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Scene);