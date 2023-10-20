#include "CollisionResult.h"

CollisionResult::CollisionResult(bool collision) :
	_collision(collision)
{
}

CollisionResult::CollisionResult(bool collision, std::shared_ptr<BoxCollider> objectA, std::shared_ptr<BoxCollider> objectB, bool isTrigger) :
	_collision(collision), _objectA(objectA), _objectB(objectB), _isTrigger(isTrigger)
{
}

CollisionResult::CollisionResult(bool collision, std::shared_ptr<BoxCollider> objectA, std::shared_ptr<BoxCollider> objectB, glm::vec3 directionVector, float distance):
	_collision(collision), _objectA(objectA), _objectB(objectB), _directionVector(directionVector), _distance(distance)
{
	_separationVector = directionVector * distance;
}

bool CollisionResult::GetCollision()
{
	return _collision;
}

std::shared_ptr<BoxCollider> CollisionResult::GetObjectA()
{
	return _objectA;
}

std::shared_ptr<BoxCollider> CollisionResult::GetObjectB()
{
	return _objectB;
}

glm::vec3 CollisionResult::GetDirectionVector()
{
	return _directionVector;
}

float CollisionResult::GetDistance()
{
	return _distance;
}

glm::vec3 CollisionResult::GetSeparationVector()
{
	return _separationVector;
}

bool CollisionResult::GetIsTrigger()
{
	return _isTrigger;
}