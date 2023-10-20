#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Core/CollisionManager.h"

class BoxCollider;

class CollisionResult
{
public:
	CollisionResult(bool collision);
	CollisionResult(bool collision, std::shared_ptr<BoxCollider> objectA, std::shared_ptr<BoxCollider> objectB, bool isTrigger = true);
	CollisionResult(bool collision, std::shared_ptr<BoxCollider> objectA, std::shared_ptr<BoxCollider> objectB, glm::vec3 directionVector, float distance);

	bool GetCollision();
	std::shared_ptr<BoxCollider> GetObjectA();
	std::shared_ptr<BoxCollider> GetObjectB();
	glm::vec3 GetDirectionVector();
	float GetDistance();
	glm::vec3 GetSeparationVector();
	bool GetIsTrigger();

private:
	bool _collision;
	std::shared_ptr<BoxCollider> _objectA;
	std::shared_ptr<BoxCollider> _objectB;
	glm::vec3 _directionVector;
	float _distance;
	glm::vec3 _separationVector;
	bool _isTrigger = false;
};
