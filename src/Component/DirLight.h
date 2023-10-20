#pragma once
#include "LightBase.h"

/// <summary>
/// Directional light component
/// </summary>
class DirLight : public LightBase
{
public:
	DirLight(glm::vec3 direction, glm::vec3 color, glm::vec3 ambient,
		glm::vec3 specular);
	DirLight();

	void Input() override;
	void Update() override;
	void Draw(std::shared_ptr<Transform> transform) override;

	void SetUp() override;

	virtual std::shared_ptr<Component> GetCopyComponent() override;

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			cereal::base_class<LightBase>(this),
			CEREAL_NVP(m_direction),
			CEREAL_NVP(m_ambient),
			CEREAL_NVP(m_specular)
		);
	}

private:
	glm::vec3 m_direction;
	glm::vec3 m_ambient;
	glm::vec3 m_specular;

};

CEREAL_REGISTER_TYPE(DirLight);
CEREAL_REGISTER_POLYMORPHIC_RELATION(LightBase,DirLight);