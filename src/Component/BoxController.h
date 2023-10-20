#pragma once

#include "core/InputManager.h"
#include "core/GameObject.h"
#include "Component/PlayerController.h"
#include "core/Time.h"
#include "Transform.h"
#include "Component.h"

class GameObject;
class Component;

class BoxController : public Component
{
public:
	BoxController();
	BoxController(float gravity, float weight);

	std::shared_ptr<Component> GetCopyComponent() override;

	void Update() override;
	void Collision(std::shared_ptr<CollisionResult> collResult) override;

	void SetUpwardSpeed(float speed);

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;
	
	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			CEREAL_NVP(_gravity),
			CEREAL_NVP(_weight)
		);
	}
	
private:
	void BoxMove();
	float _gravity = 0;
	float _weight = 1;
	float _upwardSpeed = 0;
};


CEREAL_REGISTER_TYPE(BoxController);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, BoxController);