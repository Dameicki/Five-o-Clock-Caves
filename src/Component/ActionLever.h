#pragma once

#include "core/GameObject.h"
#include "ActionBase.h"
#include "Component.h"

class GameObject; 
class Component;

class ActionLever : public ActionBase {
public:
	ActionLever();
	ActionLever(bool isActive, bool isUsable);

	std::shared_ptr<Component> GetCopyComponent() override;

	void SetUp() override;
	void Update() override;

	void ActionStart() override;
	void ActionStop() override;

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			cereal::base_class<ActionBase>(this)
		);
	}
private:
	float _targetRotation;
};

CEREAL_REGISTER_TYPE(ActionLever);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ActionBase, ActionLever);