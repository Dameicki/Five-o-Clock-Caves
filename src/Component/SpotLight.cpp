#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 direction, glm::vec3 color, glm::vec3 specular, glm::vec3 ambient, 
	float constant, float linear, float quadratic): m_direction(direction),
	 m_specular(specular), m_ambient(ambient), constant(constant), linear(linear), quadratic(quadratic), cutOff(1.0f), outerCutOff(0.0f) ,LightBase(LightType::spot, color)
{
	type = SPOT_LIGHT;
}

void SpotLight::SetUp()
{
	if (enabled)
		LightBase::SetUp();

}

void SpotLight::Input(){}

void SpotLight::Update()
{
	ShaderSystem::GetInstance().UniformSpotLight(m_gameObject->m_transform->GetGlobalPosition(), m_direction, m_color, m_specular, m_ambient, constant, 
		linear, quadratic, cutOff, outerCutOff, visible, id);
}

void SpotLight::Draw(std::shared_ptr<Transform> transform) {}

std::shared_ptr<Component> SpotLight::GetCopyComponent()
{
	std::shared_ptr<Component> copyComponent = std::make_shared<SpotLight>(SpotLight(m_direction,m_color,m_specular,m_ambient,constant,linear,quadratic));
	return copyComponent;
}

void SpotLight::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	ImGui::Text(" ");		// Odstêp

	string tmp = "[ Spot Light " + to_string(index) + " ]";// nawa jest tu
	if (ImGui::CollapsingHeader(tmp.c_str()))
	{
		bool enabledTMP = enabled;	// stan w³¹cznika
		ImGui::Checkbox("enabled", &enabledTMP);

		ImGui::ColorEdit3("light color", (float*)&m_color);			// parametry kmponentu
		ImGui::ColorEdit3("light specular", (float*)&m_specular);	// parametry kmponentu
		ImGui::InputFloat("constant", (float*)&constant);			// parametry kmponentu
		ImGui::InputFloat("linear", (float*)&linear);				// parametry kmponentu
		ImGui::InputFloat("quadratic", (float*)&quadratic);			// parametry kmponentu
		ImGui::InputFloat3("direction", (float*)&m_direction, "%.3f");
		ImGui::InputFloat("cut Off", &cutOff);
		ImGui::InputFloat("outer CutOff", &outerCutOff);

		this->SetEnabled(enabledTMP);			// metoda która reaguje na stan w³¹cznika
	}
}
