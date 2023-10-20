#pragma once

#include "core/GameObject.h"
#include "Component.h"

class GameObject; 
class Component;

class ActionBase : public Component {
public:
	ActionBase();

	void SetIsActive(bool state);
	bool GetIsActive();

	void SetIsUsable(bool state);
	bool GetIsUsable();

	virtual void Start();

	void Update() override;

	void Active();

	void SetInactive();

	virtual void ActionStart();
	virtual void Run();
	virtual void Return();
	virtual void ActionStop();

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			CEREAL_NVP(_isActive),
			CEREAL_NVP(_isUsable)
		);
	}
	
protected:
	bool _isActive = false;
	bool _isUsable = true;
};

CEREAL_REGISTER_TYPE(ActionBase);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, ActionBase);