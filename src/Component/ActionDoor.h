#pragma once

#include "core/GameObject.h"
#include "ActionBase.h"
#include "Component.h"

class GameObject; 
class Component;

class ActionDoor : public ActionBase {
public:
	ActionDoor();
	ActionDoor(bool locked);

	std::shared_ptr<Component> GetCopyComponent() override;

	bool GetLocked();

	void ActionStart() override;
	void ActionStop()override;

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			cereal::base_class<ActionBase>(this),
			CEREAL_NVP(_locked)
		);
	}

private:
	bool _locked = false;
};

CEREAL_REGISTER_TYPE(ActionDoor);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ActionBase, ActionDoor);