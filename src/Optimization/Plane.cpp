#include "Plane.h"

Plane::Plane(glm::vec3 normal, float distance): _normal(normal), _distance(distance)
{
}

void Plane::Normalize()
{
	float flScale = 1 / glm::length(_normal);
	_normal.x *= flScale;
	_normal.y *= flScale;
	_normal.z *= flScale;
	_distance *= flScale;
}
