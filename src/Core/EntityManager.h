#pragma once
#define ENTITY EntityManager::GetInstance()
#include "GameObject.h"

class EntityManager
{
public:
	//Daje instancje singletona
	static EntityManager& GetInstance();

	std::shared_ptr<GameObject> GetEntity(std::string name);

	void AddEntity(std::shared_ptr<GameObject> entity);
	void RemoveEntity(std::shared_ptr<GameObject> entity);

private:
	EntityManager();
	EntityManager(EntityManager const&);
	std::list<std::shared_ptr<GameObject>> _entityList;
};
