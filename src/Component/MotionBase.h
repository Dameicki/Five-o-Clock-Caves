#pragma once

#include <glm/vec3.hpp>

#include "core/GameObject.h"
#include "Component.h"
#include "Core/Time.h"

class GameObject; 
class Component;

class MotionBase : public Component {
public:
	MotionBase();

	glm::vec3 GetTmpMovementVector();

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			CEREAL_NVP(_movementVector),
			CEREAL_NVP(_tmpMovementVector),
			CEREAL_NVP(_timeToFinish),
			CEREAL_NVP(_timer)
		);
	}

protected:
	glm::vec3 _movementVector;
	glm::vec3 _tmpMovementVector;
	float _timeToFinish;
	float _timer = 0;
};

CEREAL_REGISTER_TYPE(MotionBase);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, MotionBase);