#pragma once

#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "core/GameObject.h"
#include "core/CollisionManager.h"
#include "Component.h"
#include "Transform.h"
#include "../Rendering/ShaderSystem.h"
#include <iostream>
#include <memory>

class GameObject; 
class CollisionResult;

enum CollisionLayer {
	DEFAULT,			// 0 
	GROUND,				// 1
	PLAYER,				// 2
	LEAF,				// 3
	DEATH,				// 4
	SPAWN1,				// 5
	SPAWN2,				// 6
	LEVER_COLL,			// 7
	INTERACTABLE_COLL,	// 8
	COG,				// 9
	DOOR,				// 10
	TEAPOT_COLL			// 11
};


class BoxCollider: public Component, public std::enable_shared_from_this<BoxCollider> {
public:
	BoxCollider(glm::vec3 centerOffset = glm::vec3(0.0f), glm::vec3 size = glm::vec3(1.0f), bool isStatic = true, bool isTrigger = false, CollisionLayer collisionLayer = DEFAULT);

	void SetUp() override;
	void Input() override;
	void Update() override;
	void Draw(std::shared_ptr<Transform> transform) override;
	void OnEnabled() override;
	void OnDisabled() override;

	std::shared_ptr<Component> GetCopyComponent() override;

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;
	
	glm::vec3 GetCenterPos();
	glm::vec3 GetSize();
	bool GetIsTrigger();
	CollisionLayer GetCollisionLayer();

	void SetColor(glm::vec3 color);
	void SetIsStatic(bool state);
	void SetIsTrigger(bool state);
	void SetCollisionLayer(CollisionLayer layer);
	void UpdateCollider();

	void CallCollision(std::shared_ptr<CollisionResult> collisionResult);
	void CallTrigger(std::shared_ptr<CollisionResult> collisionResult);

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(cereal::base_class<Component>(this),
			CEREAL_NVP(_centerTransform),
			CEREAL_NVP(_centerPosition),
			CEREAL_NVP(_size),
			CEREAL_NVP(_centerOffset),
			CEREAL_NVP(_color),
			CEREAL_NVP(_collisionLayer),
			CEREAL_NVP(_isStatic),
			CEREAL_NVP(_isTrigger)
		);
	}

private:
	glm::mat4 _centerTransform = glm::mat4(0.0f);
	glm::vec3 _centerPosition = glm::vec3(0.0f);
	glm::vec3 _size;
	glm::vec3 _centerOffset;
	glm::vec3 _color = glm::vec3(0.0f, 1.0f, 0.0f);
	CollisionLayer _collisionLayer;
	bool _isStatic;
	bool _isTrigger;
};

CEREAL_REGISTER_TYPE(BoxCollider);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, BoxCollider);