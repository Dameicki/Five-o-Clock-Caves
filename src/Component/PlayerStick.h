#pragma once

#include <glm/vec3.hpp>

#include "core/GameObject.h"
#include "Component.h"
#include "MotionBase.h"
#include "Platform.h"

class GameObject; 
class Component;

class PlayerStick : public Component {
public:
	PlayerStick(std::shared_ptr<Component> platformPtr = nullptr, bool type = true);

	std::shared_ptr<Component> GetCopyComponent() override;

	void Trigger(std::shared_ptr<CollisionResult> collResult) override;

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	void AddPlatformPtr(std::shared_ptr<Platform> ptr);

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			CEREAL_NVP(_platformPtr),
			CEREAL_NVP(_type)
		);
	}


private:
	std::shared_ptr<Component> _platformPtr;
	bool _type = true;
};
CEREAL_REGISTER_TYPE(PlayerStick);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, PlayerStick);