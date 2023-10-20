#pragma once

#include "MotionBase.h"

class LinearMotion : public MotionBase {
public:
	LinearMotion(glm::vec3 movementVector = glm::vec3(0.0f), float timeToFinish = 1, bool finish = false);

	void Update() override;

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;


	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			cereal::base_class<MotionBase>(this),
			CEREAL_NVP(_finish)
		);
	}


private:
	bool _finish;
};
CEREAL_REGISTER_TYPE(LinearMotion);
CEREAL_REGISTER_POLYMORPHIC_RELATION(MotionBase, LinearMotion);