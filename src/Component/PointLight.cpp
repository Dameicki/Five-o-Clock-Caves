#include "PointLight.h"

PointLight::PointLight(glm::vec3 color, glm::vec3 specular, glm::vec3 ambient, float constant, float linear, float quadratic):
	m_specular(specular), m_ambient(ambient), constant(constant), linear(linear), quadratic(quadratic)//,LightBase(LightType::point, color)
{
	id = -1; // jeszcze nie ma na liœcie
	type = POINT_LIGHT;

	lightType = LightType::point;
	m_color = color;

	//cout << ">>>>>>  PointLight()" << endl;
}

void PointLight::Update()
{
	//if(visible)
	//	ShaderSystem::GetInstance().UniformPointLight(m_gameObject->m_transform->GetGlobalPosition(), m_color, m_specular, m_ambient, constant, linear, quadratic, enabled, id);
	//else
	//	ShaderSystem::GetInstance().UniformPointLight(m_gameObject->m_transform->GetGlobalPosition(), m_color, m_specular, m_ambient, constant, linear, quadratic, false, id);
	ShaderSystem::GetInstance().UniformPointLight(m_gameObject->m_transform->GetGlobalPosition(), m_color, m_specular, m_ambient, constant, linear, quadratic, visible, id);

}

void PointLight::SetUp()
{
	if (enabled)
		LightBase::SetUp();
}

void PointLight::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	ImGui::Text(" ");		// Odstêp

	string tmp = "[ Point Light " + to_string(index) + " ]";// nawa jest tu
	if (ImGui::CollapsingHeader(tmp.c_str()))
	{
		bool enabledTMP = enabled;	// stan w³¹cznika
		ImGui::Checkbox("enabled", &enabledTMP);

		ImGui::ColorEdit3("light color", (float*)&m_color);			// parametry kmponentu
		ImGui::ColorEdit3("light specular", (float*)&m_specular);	// parametry kmponentu
		ImGui::InputFloat("constant", (float*)&constant);			// parametry kmponentu
		ImGui::InputFloat("linear", (float*)&linear);				// parametry kmponentu
		ImGui::InputFloat("quadratic", (float*)&quadratic);			// parametry kmponentu

		this->SetEnabled(enabledTMP);			// metoda która reaguje na stan w³¹cznika
	}
}

std::shared_ptr<Component> PointLight::GetCopyComponent()
{
	std::shared_ptr<Component> copyComponent = std::make_shared<PointLight>(PointLight(m_color, m_specular, m_ambient, constant, linear, quadratic));
	return copyComponent;
}
