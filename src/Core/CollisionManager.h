#pragma once
#define COLLISION CollisionManager::GetInstance()

#include <list>
#include <GLFW/glfw3.h>
#include <component/BoxCollider.h>
#include <core/CollisionResult.h>

class BoxCollider;
class CollisionResult;

class CollisionManager
{
public:
	
	//Daje instancje singletona
	static CollisionManager& GetInstance();

	void Update();

	void AddStaticObject(std::shared_ptr<BoxCollider> staticObject);
	void AddDynamicObject(std::shared_ptr<BoxCollider> dynamicObject);
	void AddCollision(std::shared_ptr<CollisionResult> collision);
	void AddTrigger(std::shared_ptr<CollisionResult> trigger);
	void ClearLists();
	void AddSpawnPoint(std::shared_ptr<GameObject> spawnPoint);
	void UpdateColliders();
	void RemoveCollider(std::shared_ptr<BoxCollider> collider, bool type);
	std::shared_ptr<CollisionResult> CheckCollision(std::shared_ptr<BoxCollider> a, std::shared_ptr<BoxCollider> b);

	glm::vec3 CalculateDirection(glm::vec3 axisDiff, glm::vec3 size);

	char MaxElement(glm::vec3 vec);
private:
	CollisionManager();
	CollisionManager(CollisionManager const&);

	std::list<std::shared_ptr<BoxCollider>> _staticObjects;
	std::list<std::shared_ptr<BoxCollider>> _dynamicObjects;
	std::list<shared_ptr<CollisionResult>> _currentFrameCollisions;
	std::list<shared_ptr<CollisionResult>> _currentFrameTriggers;
	std::vector<shared_ptr<GameObject>> _spawnPoints;

	glm::vec3 _axisDiff = glm::vec3(0.0f);
	glm::vec3 _axisSize = glm::vec3(0.0f);
	glm::vec3 _directionVector = glm::vec3(0.0f);
	glm::vec3 _spawnPoint = glm::vec3(0.0f);

	int _MaxElementIndex = 0;
};
