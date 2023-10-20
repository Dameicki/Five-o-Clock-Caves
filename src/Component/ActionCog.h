#pragma once

#include "core/GameObject.h"
#include "ActionBase.h"
#include "Component.h"

class GameObject; 
class Component;

class ActionCog : public ActionBase {
public:
	ActionCog();
	ActionCog(int axis, float rotationSpeed, bool isActive, bool isUsable);

	std::shared_ptr<Component> GetCopyComponent() override;

	void Run() override;

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			cereal::base_class<ActionBase>(this),
			CEREAL_NVP(_axis),
			CEREAL_NVP(_rotationSpeed)
		);
	}
private:
	int _axis = 2;
	float _rotationSpeed = 1;
};

CEREAL_REGISTER_TYPE(ActionCog);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ActionBase, ActionCog);