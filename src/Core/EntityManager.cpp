#include "EntityManager.h"

EntityManager::EntityManager()
{

}

EntityManager& EntityManager::GetInstance()
{
	static EntityManager* instance = nullptr;

	if (instance == nullptr)
		instance = new EntityManager();

	return *instance;
}

std::shared_ptr<GameObject> EntityManager::GetEntity(std::string name)
{
	for (auto& entity : _entityList)
	{
		if (entity->m_name == name)
		{
			return entity;
		}
	}
	return std::shared_ptr<GameObject>(nullptr);
}

void EntityManager::AddEntity(std::shared_ptr<GameObject> entity)
{
	bool flag = true;

	for (auto& en : _entityList)
	{
		if (en->m_name == entity->m_name)
			flag = false;
	}

	if (flag)
		_entityList.push_back(entity);

}

void EntityManager::RemoveEntity(std::shared_ptr<GameObject> entity)
{
	_entityList.remove(entity);
}


