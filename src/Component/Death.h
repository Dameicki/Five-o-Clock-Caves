#pragma once
#include "Core/GameObject.h"
#include "Component.h"
#include "PlayerController.h"

class GameObject;
class Component;

class Death : public Component
{
public:
	Death();

	void Trigger(std::shared_ptr<CollisionResult> collResult) override;

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			CEREAL_NVP(_spawnPoint)
		);
	}

private:
	friend class cereal::access;
	glm::vec3 _spawnPoint = glm::vec3(0.0f);
	int side = -1;
};
CEREAL_REGISTER_TYPE(Death);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Death);