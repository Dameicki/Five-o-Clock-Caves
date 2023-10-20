 #pragma once

//#include "../core/GameObject.h"
//#include "../Rendering/ShaderSystem.h"

#include <memory>
#include "Component.h"
#include "Core/GameObject.h"
#include "Transform.h"

#include "../Rendering/ShaderSystem.h"
#include "../Rendering/LightManager.h"

class GameObject;
class ImguiSystem;
class Transform;
class ShaderSystem;
class Component;

enum LightType;

class LightBase : public Component, public std::enable_shared_from_this<LightBase>
{
public:
	LightBase();
	LightBase(LightType lightType);
	LightBase(LightType lightType, glm::vec3 color = glm::vec3{ 0.0f,0.0f,0.0f });
	int GetID();
	void SetID(int newID);

	void SetUp() override;

	virtual void Input() override;
	virtual void Update() override;
	virtual void Draw(std::shared_ptr<Transform> transform) override;

	bool FrustumCulling();

	virtual void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(cereal::base_class<Component>(this),
			CEREAL_NVP(lightType),
			CEREAL_NVP(m_color)
			);
	}


protected:

	friend class cereal::access;

	void OnEnabled() override;
	void OnDisabled() override;

	bool visible = false;

	int id;
	LightType lightType;
	glm::vec3 m_color;
}; 
CEREAL_REGISTER_TYPE(LightBase);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, LightBase);