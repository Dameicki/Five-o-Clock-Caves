#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
}

CollisionManager& CollisionManager::GetInstance()
{
	static CollisionManager* instance = NULL;

	if (instance == NULL)
		instance = new CollisionManager();

	return *instance;
}

void CollisionManager::Update()
{
	for (auto& objA : _dynamicObjects)
	{
		for (auto& objB : _dynamicObjects)
		{
			if (objA != objB)
			{
				std::shared_ptr<CollisionResult> collResult = CheckCollision(objA, objB);
				if (collResult->GetCollision())
				{
					if (!collResult->GetIsTrigger())
					{
						objA->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
						objB->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
						AddCollision(collResult);
					}
					else {
						AddTrigger(collResult);
					}
				}
				else {
					objA->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
					objB->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
				}
			}
		}

		for (auto& objB : _staticObjects)
		{
			std::shared_ptr<CollisionResult> collResult = CheckCollision(objA, objB);
			if (collResult->GetCollision())
			{
				if (!collResult->GetIsTrigger())
				{
					AddCollision(collResult);
				}
				else {
					AddTrigger(collResult);
				}
			}
		}
	}
	while (!_currentFrameTriggers.empty())
	{
		_currentFrameTriggers.front()->GetObjectB()->CallTrigger(_currentFrameTriggers.front());
		_currentFrameTriggers.front()->GetObjectA()->CallTrigger(_currentFrameTriggers.front());
		_currentFrameTriggers.pop_front();
	}

	while (!_currentFrameCollisions.empty())
	{
		_currentFrameCollisions.front()->GetObjectA()->CallCollision(_currentFrameCollisions.front());
		_currentFrameCollisions.pop_front();
	}

}

void CollisionManager::AddStaticObject(std::shared_ptr<BoxCollider> staticObject)
{
	//std::cout << "Adding static object to collision." << std::endl;
	_staticObjects.push_back(staticObject);
}

void CollisionManager::AddDynamicObject(std::shared_ptr<BoxCollider> dynamicObject)
{
	//std::cout << "Adding dynamic object to collision." << std::endl;
	_dynamicObjects.push_back(dynamicObject);
}

void CollisionManager::AddCollision(std::shared_ptr<CollisionResult> collision)
{
	_currentFrameCollisions.push_back(collision);
}

void CollisionManager::AddTrigger(std::shared_ptr<CollisionResult> trigger)
{
	_currentFrameTriggers.push_back(trigger);
}

void CollisionManager::ClearLists()
{
	_staticObjects.clear();
	_dynamicObjects.clear();
}

void CollisionManager::AddSpawnPoint(std::shared_ptr<GameObject> spawnPoint)
{
	_spawnPoints.push_back(spawnPoint);
}

void CollisionManager::UpdateColliders()
{
	for (auto& dyn : _dynamicObjects)
	{
		dyn->UpdateCollider();
	}
	for (auto& sta : _staticObjects)
	{
		sta->UpdateCollider();
	}
}

void CollisionManager::RemoveCollider(std::shared_ptr<BoxCollider> collider, bool type)
{
	if (type)
		_dynamicObjects.remove(collider);
	else
		_staticObjects.remove(collider);
	
}

std::shared_ptr<CollisionResult> CollisionManager::CheckCollision(std::shared_ptr<BoxCollider> a, std::shared_ptr<BoxCollider> b)
{
	_axisDiff = glm::vec3(a->GetCenterPos().x - b->GetCenterPos().x, a->GetCenterPos().y - b->GetCenterPos().y, a->GetCenterPos().z - b->GetCenterPos().z);
	_axisSize = glm::vec3(a->GetSize().x + b->GetSize().x, a->GetSize().y + b->GetSize().y, a->GetSize().z + b->GetSize().z);

	bool x = glm::abs(_axisDiff.x) < (_axisSize.x);
	bool y = glm::abs(_axisDiff.y) < (_axisSize.y);
	bool z = glm::abs(_axisDiff.z) < (_axisSize.z);

	bool collision = x && y && z;

	if (!collision) return std::make_shared<CollisionResult>(CollisionResult(collision));
	else {
		if (!b->GetIsTrigger())
		{
			_directionVector = CalculateDirection(_axisDiff, _axisSize);
			return std::make_shared<CollisionResult>(CollisionResult(collision, a, b, _directionVector, glm::abs(_axisDiff[_MaxElementIndex]) - _axisSize[_MaxElementIndex]));
		}
		else {
			return std::make_shared<CollisionResult>(CollisionResult(collision, a, b, true));
		}
	}
}

glm::vec3 CollisionManager::CalculateDirection(glm::vec3 axisDiff, glm::vec3 size)
{
	_MaxElementIndex = MaxElement(glm::abs(axisDiff)-size);
	switch (_MaxElementIndex)
	{
	case 0:
		if (axisDiff.x < 0) return glm::vec3(1.0f, 0.0f, 0.0f);
		else return glm::vec3(-1.0f, 0.0f, 0.0f);
	case 1:
		if (axisDiff.y < 0) return glm::vec3(0.0f, 1.0f, 0.0f);
		else return glm::vec3(0.0f, -1.0f, 0.0f);
	case 2:
		if (axisDiff.z < 0) return glm::vec3(0.0f, 0.0f, 1.0f);
		else return glm::vec3(0.0f, 0.0f, -1.0f);
	}
}

char CollisionManager::MaxElement(glm::vec3 vec)
{
	if (vec.y < vec.x && vec.x > vec.z)
	{
		return 0;
	}

	else if (vec.x < vec.y && vec.y > vec.z)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}