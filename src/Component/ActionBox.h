#pragma once

#include "core/GameObject.h"
#include "Component/BoxController.h"
#include "ActionBase.h"
#include "Component.h"

class GameObject; 
class Component;
class BoxController;

class ActionBox : public ActionBase {
public:
	ActionBox();

	std::shared_ptr<Component> GetCopyComponent() override;

	void ActionStart() override;
	void ActionStop() override;

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			cereal::base_class<ActionBase>(this),
			CEREAL_NVP(_startPosition)
		);
	}
private:
	glm::vec3 _startPosition = glm::vec3(0.0f);
	void ResetPosition();
};

CEREAL_REGISTER_TYPE(ActionBox);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ActionBase, ActionBox);