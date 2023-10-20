#pragma once
#include "Interactable.h"
#include "Pickable.h"
#include "Teapot.h"

enum TeaType;
class Teapot;

class Leaf : public Pickable
{
public :
	Leaf(TeaType teaType);
	Leaf();

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override; 

	virtual std::shared_ptr<Component> GetCopyComponent() override;

	TeaType GetTeaType();

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			cereal::base_class<Interactable>(this),
			CEREAL_NVP(teaType)
			);
	}

protected:
	TeaType teaType;
	int iTeaType;
};

CEREAL_REGISTER_TYPE(Leaf);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Pickable, Leaf);