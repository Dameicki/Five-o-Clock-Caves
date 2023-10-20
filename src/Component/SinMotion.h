#pragma once

#include "MotionBase.h"

class SinMotion : public MotionBase {
public:
	SinMotion(glm::vec3 movementVector = glm::vec3(0.0f), float timeToFinish = 1);

	void Update() override;

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			cereal::base_class<MotionBase>(this)
		);
	}


	
};

CEREAL_REGISTER_TYPE(SinMotion);
CEREAL_REGISTER_POLYMORPHIC_RELATION(MotionBase, SinMotion);