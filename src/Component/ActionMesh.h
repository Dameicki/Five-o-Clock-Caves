#pragma once

#include "core/GameObject.h"
#include "ActionBase.h"
#include "Component.h"

class GameObject;
class Component;

class ActionMesh : public ActionBase {
public:
	ActionMesh();

	std::shared_ptr<Component> GetCopyComponent() override;

	void SetUp()override;

	void ActionStart() override;
	void ActionStop()override;

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
	shared_ptr<MeshRenderer> _meshRenderer;
};

CEREAL_REGISTER_TYPE(ActionMesh);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ActionBase, ActionMesh);