#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//..::STL::..
#include <list>
#include <memory>
#include <string>
#include <iostream>

//..::CEREAL::..
#include <cereal/types/memory.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/string.hpp>				//Michał to do odkomentowania jak bedzie działać
#include <cereal/archives/xml.hpp>
#include <cereal/access.hpp>

//#include <cereal/archives/json.hpp>

#include "../component/Component.h"
#include "../component/Transform.h"
#include "../component/MeshRenderer.h"
#include "../component/BoundingSphere.h"
#include "CollisionManager.h"
#include "CollisionResult.h"
#include "../gui/imguiSystem.h"
#include "Optimization/Frustum.h"
#include "Core/EntityManager.h"

class ImguiSystem;
class BoundingSphere;
// -------- TYMCZASOWE
enum ComponentType {
	NONE,				// 0
	TRANSFORM,			// 1
	PLAYER_CONTROLLER,	// 2
	BOX_COLLIDER,		// 3
	LINEAR_MOTION,		// 4
	SIN_MOTION,			// 5
	MESH_RENDERER,		// 6
	PLAYER_STICK,		// 7
	POINT_LIGHT,		// 8
	SPOT_LIGHT,			// 9
	SPRITE_RENDERER,	// 10
	INTERACTABLE,		// 11
	LEVER,				// 12
	ACTION_BASE,		// 13
	ACTION_LEVER,		// 14
	PLATFORM,			// 15
	PLAYER_INTERACTION,	// 16
	PUZZLE_CHECKER,		// 17
	COG_COMP,			// 18
	DOOR_COMP,			// 19
	ACTION_COG,			// 20
	DEATH_ZONE,			// 21
	BOX_CONTROLLER,		// 22
	PLACE_FOR_COG,		// 23
	ACTION_BOX,			// 24
	ACTION_MESH,		// 25
	ACTION_DOOR,		// 26
	ANIMATOR,			// 27
	GOOLD_DOOR_COMP,	// 28
	TEAPOT,				// 29
	LEAF_COMP,			// 30
	LEVEL,				// 31
	ALL_PLAYERS,		// 32
	DIR_LIGHT,			// 33
	SCENE,				// 34
	CAMERA_CONTROLLER	// 35
};
// -------- TYMCZASOWE



class GameObject: public std::enable_shared_from_this<GameObject> {
public:
	template <class T>
	std::shared_ptr<T> GetComponent(ComponentType type) {
		for (auto& component : m_components)
		{
			if (component->GetType() == type)
			{
				return dynamic_pointer_cast<T>(component);
			}
		}
		return nullptr;
	}

	template <class T>
	std::list<std::shared_ptr<T>> GetComponentsList(ComponentType type) {
		std::list<std::shared_ptr<T>> currentList = std::list<std::shared_ptr<T>>();
		for (auto& component : m_components)
		{
			if (component->GetType() == type)
			{
				currentList.push_back(dynamic_pointer_cast<T>(component));
			}
		}
		return currentList;
	}

	template <class T>
	std::list<std::shared_ptr<T>> GetComponentsListInChildren(ComponentType type) {
		std::list<std::shared_ptr<T>> currentList = std::list<std::shared_ptr<T>>();
		currentList = GetComponentsList<T>(type);
		for (auto& child : m_children)
		{
			std::list<std::shared_ptr<T>> childList = child->GetComponentsListInChildren<T>(type);
			//cout << childList.size()<<". in " <<child->m_name << endl;
			currentList.splice(currentList.end(), childList);
		}
		return currentList;
	}


	GameObject(std::string name, int depth, std::list<std::shared_ptr<GameObject>> children, std::shared_ptr<Transform> transform, std::list<std::shared_ptr<Component>> components, bool ena);

	GameObject(std::string name);// Konstruktor do tworzenia pierwszego obiektu "root"

	GameObject(std::shared_ptr<GameObject> parent, std::string name); // Konstruktor dla wszystkich obiektów oprócz "roota"
	//GameObject(std::list<std::shared_ptr<GameObject>> children, std::string name); // Konstruktor dla wszystkich obiektów oprócz "roota"
	//GameObject();

	static shared_ptr<GameObject> GetRootObject(shared_ptr<GameObject> object);// metoda idzie po parentach aż dojdzie do roota i go zwraca

	void SetEnabled(bool newEnabled, bool byParent=false); // jeśli newEnabled zmieni stan to wywoła metodę OnEnabled lub OnDisable

	void Load();
	void SetUp(); // wywołuje się raz przed petlą gry

	void Input();
	void Update();
	void Trigger(std::shared_ptr<CollisionResult> collResult);
	void Collision(std::shared_ptr<CollisionResult> collResult);
	void CheckIfDrawable();
	void CheckIfDrawableInCurrentRoom();
	void Draw();
	void DrawCurrentRoom();
	unsigned int CreateDebugQuad();
	void DrawShadowMap();

	void DrawToShadowMap();

	void AddParent(std::shared_ptr<GameObject> parent);
	void AddChild(std::shared_ptr<GameObject> child);
	void RemoveChild(std::shared_ptr<GameObject> child);
	void DestroyAllChild();
	void Destroy();
	void SetNewParent(std::shared_ptr<GameObject> newParent);
	void DuplicateObject(); 
	void FullDuplicateObject(std::shared_ptr<GameObject> objectToCopy);

	void AddComponent(std::shared_ptr<Component> component);
	void RemoveComponent(std::shared_ptr<Component> component);

	void ImGuiAddButtonToHierarchy(ImguiSystem* imguiSystem, bool show = false);
	void ImGuiAddToInspector(ImguiSystem* imguiSystem);
	
	void SetBSSetup(bool state);
	void FrustumCulling();
	
	void UpdateColliders();

	//std::shared_ptr<GameObject> GetObjectReference(std::string name);

	// -------- TYMCZASOWE
	std::shared_ptr<Component> GetComponent(ComponentType type);

	// -------- TYMCZASOWE

	std::shared_ptr<GameObject> m_parent;
	std::shared_ptr<Transform> m_transform;
	std::shared_ptr<BoundingSphere> m_boundingSphere;
	//std::shared_ptr<PointLight> m_renderer;
	std::string m_name;
	void Serialize(std::string path = "Scene.xml");
	void Deserialize(std::string path = "Scene.xml");

private:
	friend class cereal::access;
	//GameObject() {}
	void OnEnabled();  // jest wywoływana kiedy enabled zmieni się z false na true
	void OnDisabled(); // jest wywoływana kiedy enabled zmieni się z true na false

	int m_depth;
	std::list<std::shared_ptr<GameObject>> m_children;
	std::list<std::shared_ptr<Component>> m_components;
	bool enabled;
	bool drawable;
	bool bsSetup;

	

	template<class Archive>
	 void serialize(Archive& archive)
	{
		archive(
			CEREAL_NVP(enabled),
			CEREAL_NVP(m_name),
			CEREAL_NVP(m_depth),
			CEREAL_NVP(m_children),
			CEREAL_NVP(m_transform), 
			CEREAL_NVP(m_components)
		);
	}


	template<class Archive> 
	static void load_and_construct(Archive& ar, cereal::construct<GameObject>& construct)
	{
		std::string name;
		int depth;
		std::list<std::shared_ptr<GameObject>> children = std::list<std::shared_ptr<GameObject>>();
		std::list<std::shared_ptr<Component>> components = std::list<std::shared_ptr<Component>>();
		std::shared_ptr<Transform> transform = std::make_shared<Transform>();
		bool enabled;

		//std::list<std::shared_ptr<GameObject>> temp = std::list<std::shared_ptr<GameObject>>();
		ar(enabled,name,depth,children,transform,components);
		construct(name, depth, children, transform, components,enabled);
		//construct->serialize(ar);
	}


};