#pragma once

//#include "Core/GameObject.h"
//#include "../Rendering/ShaderSystem.h"

#include <memory>
#include <string>

#include <cereal/types/polymorphic.hpp>
#include "../Core/Time.h"

class GameObject;
class ImguiSystem;
class Transform;
class ShaderSystem;
class CollisionResult;

class Component
{
public:
	Component();
	void SetGameObject(std::shared_ptr<GameObject> gameObject);

	bool GetEnabled();
	// -------- TYMCZASOWE
	int GetType();
	std::shared_ptr<GameObject> GetOwner();
	// -------- TYMCZASOWE
	void SetEnabled(bool newEnabled, bool byObject = false); // jeœli newEnabled zmieni stan to wywo³a metodê OnEnabled lub OnDisable
	virtual void OnEnabled();  // jest wywo³ywana kiedy enabled zmieni siê z false na true
	virtual void OnDisabled(); // jest wywo³ywana kiedy enabled zmieni siê z true na false

	virtual void Load();
	virtual void SetUp(); // wywo³uje siê raz przed petl¹ gry

	virtual void Input();
	virtual void Update();
	virtual void Trigger(std::shared_ptr<CollisionResult> collResult);
	virtual void Collision(std::shared_ptr<CollisionResult> collResult);
	virtual void Draw(std::shared_ptr<Transform> transform);
	virtual void DrawToShadowMap(std::shared_ptr<Transform> transform);

	virtual void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index); // wyœwieltla swoje parametry na panelu imgui "inspector"

	virtual std::shared_ptr<Component> GetCopyComponent();

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(CEREAL_NVP(enabled), CEREAL_NVP(type), CEREAL_NVP(m_gameObject));
	}
	bool Delay(float timer, bool repeat);
	void ClearDelay();

protected:

	std::shared_ptr<GameObject> m_gameObject;

	bool enabled;
	int type;
	float timeLeft;
	int delayStatus;
};

CEREAL_REGISTER_TYPE(Component);