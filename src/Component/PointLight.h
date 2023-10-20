#pragma once

//#include "../core/GameObject.h"
//#include "../Rendering/ShaderSystem.h"

#include <memory>
#include "Component.h"
#include "Core/GameObject.h"
#include "Transform.h"
#include "LightBase.h"

#include "../Rendering/ShaderSystem.h"
#include "../Rendering/LightManager.h"

class GameObject;
class ImguiSystem;
class Transform;
class ShaderSystem;
class Component;
class LightBase;

class PointLight : public LightBase
{
public:
	PointLight(glm::vec3 color = glm::vec3(1.0f), glm::vec3 specular = glm::vec3(1.0f), glm::vec3 ambient = glm::vec3(0.05f),
				float constant = 1.0f, float linear = 0.1f, float quadratic = 0.1f);

	void Update() override;

	void SetUp() override;

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	virtual std::shared_ptr<Component> GetCopyComponent() override;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			//cereal::base_class<Component>(this),
			cereal::base_class<LightBase>(this),
			CEREAL_NVP(m_specular),
			CEREAL_NVP(m_ambient),
			CEREAL_NVP(constant),
			CEREAL_NVP(linear),
			CEREAL_NVP(quadratic)
			);
	}

private:
	glm::vec3 m_specular;
	glm::vec3 m_ambient;

	//bool load = true;

	float constant;
	float linear;
	float quadratic;
};
CEREAL_REGISTER_TYPE(PointLight);
CEREAL_REGISTER_POLYMORPHIC_RELATION(LightBase, PointLight);