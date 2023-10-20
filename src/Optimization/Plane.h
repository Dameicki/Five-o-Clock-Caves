#pragma once

#include <glm/vec3.hpp>

#include "core/GameObject.h"

class GameObject; 

class Plane {
public:
	Plane(glm::vec3 normal, float distance);

	void Normalize();

	glm::vec3 _normal;

	float _distance;
};
