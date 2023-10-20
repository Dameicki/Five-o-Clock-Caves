#pragma once
#include <memory>
#include "Component.h"
#include "Core/GameObject.h"
#include "Transform.h"
#include "LightBase.h"

#include "../Rendering/ShaderSystem.h"
#include "../Rendering/LightManager.h"

class SpotLight :
    public LightBase
{
public:
	SpotLight(glm::vec3 direction = glm::vec3(0.0f), glm::vec3 color = glm::vec3(0.0f), glm::vec3 specular = glm::vec3(1.0f), glm::vec3 ambient = glm::vec3(0.05f),
		float constant = 1.0f, float linear = 0.1f, float quadratic = 0.1f);

	void SetUp() override;

	void Input() override;
	void Update() override;
	void Draw(std::shared_ptr<Transform> transform) override;

	virtual std::shared_ptr<Component> GetCopyComponent() override;

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			cereal::base_class<LightBase>(this),
			CEREAL_NVP(enable),
			CEREAL_NVP(m_direction),
			CEREAL_NVP(cutOff),
			CEREAL_NVP(outerCutOff),
			CEREAL_NVP(m_ambient),
			CEREAL_NVP(m_diffuse),
			CEREAL_NVP(m_specular),
			CEREAL_NVP(constant),
			CEREAL_NVP(linear),
			CEREAL_NVP(quadratic)

		);

	}



private:
	bool enable = true;

	glm::vec3 m_direction;
	float cutOff;
	float outerCutOff;

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

	float constant;
	float linear;
	float quadratic;

};

CEREAL_REGISTER_TYPE(SpotLight);
CEREAL_REGISTER_POLYMORPHIC_RELATION(LightBase, SpotLight);